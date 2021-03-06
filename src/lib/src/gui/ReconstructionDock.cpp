#define RECONSTRUCTIONDOCK_CPP
#include <gui/ReconstructionDock.hpp>
#include <gui/ReconstructionDockState.hpp>
#include <gui/ReconstructionDockTasks.hpp>
#include <gui/MainWindow.hpp>
#include <gui/DisplayFunctions.hpp>
#include <core/Stack.hpp>
#include <core/Event.hpp>
#include <core/ReconstructionState.hpp>
#include <core/Padplane.hpp>
#include <core/Tpc.hpp>
#include <core/DataHandler.hpp>
#include <core/Hdf5Wrapper.hpp>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QFutureWatcher>
#include <QtCore/QFuture>
#include <iostream>

namespace attpcfe {

  class ReconstructionDock::ReconstructionDockImpl {

  public:
    ReconstructionDockImpl(QWidget* parent) : _mainWindow{dynamic_cast<MainWindow*>(parent)} {}

    MainWindow* _mainWindow;
    std::unique_ptr<DataHandler<Hdf5Wrapper>> _dataHandler{std::make_unique<DataHandler<Hdf5Wrapper>>()};
    int _fromEvent;
    int _nEvents;
    
    std::unique_ptr<QFutureWatcher<void> > _pWatcher;
    std::unique_ptr<ReconstructionTask> _pTask;
    std::unique_ptr<QFuture<void> > _pFuture;

    // Handles to widgets ReconstructionDock took ownership of
    QPushButton* _loadPadplaneButton{nullptr};
    QPushButton* _showPadplaneButton{nullptr};
    QPushButton* _loadTpcButton{nullptr};
    QPushButton* _showTpcButton{nullptr}; 
    QPushButton* _loadDataButton{nullptr};
    QPushButton* _runButton{nullptr};
    QPushButton* _showEventButton{nullptr};
    QSpinBox* _nEventsSpin{nullptr};
    QSpinBox* _fromEventSpin{nullptr};
    
    // ReconstructionState
    std::unique_ptr<ReconstructionDockState> _state{std::make_unique<ReconstructionDockState>()};
  };

  ReconstructionDock::ReconstructionDock(QWidget* parent) : QDockWidget{parent}, _pImpl{new ReconstructionDockImpl{parent}, [](ReconstructionDockImpl* ptr){ delete ptr; }}
  {
    setWindowTitle(tr("Reconstruction"));
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setFixedSize(200, 400);

    auto layout = new QVBoxLayout{};
    _pImpl->_loadPadplaneButton = new QPushButton{"Load padplane"};
    layout->addWidget(_pImpl->_loadPadplaneButton);
    connect(_pImpl->_loadPadplaneButton, &QPushButton::clicked, this, &ReconstructionDock::loadPadplane);
    _pImpl->_showPadplaneButton = new QPushButton{"Show padplane"};
    layout->addWidget(_pImpl->_showPadplaneButton);
    connect(_pImpl->_showPadplaneButton, &QPushButton::clicked, this, &ReconstructionDock::showPadplane);
    
    _pImpl->_loadTpcButton = new QPushButton{"Load TPC"};
    layout->addWidget(_pImpl->_loadTpcButton);
    connect(_pImpl->_loadTpcButton, &QPushButton::clicked, this, &ReconstructionDock::loadTpc);
    _pImpl->_showTpcButton = new QPushButton{"Show TPC"};
    layout->addWidget(_pImpl->_showTpcButton);
    connect(_pImpl->_showTpcButton, &QPushButton::clicked, this, &ReconstructionDock::showTpc);
    
    _pImpl->_loadDataButton = new QPushButton{"Load data"};
    layout->addWidget(_pImpl->_loadDataButton);
    connect(_pImpl->_loadDataButton, &QPushButton::clicked, this, &ReconstructionDock::loadData);

    _pImpl->_fromEventSpin = new QSpinBox;
    _pImpl->_fromEventSpin->setSingleStep(1);
    _pImpl->_fromEventSpin->setValue(0);
    auto startEventLabel = new QLabel{"From event:"};
    layout->addWidget(startEventLabel);
    layout->addWidget(_pImpl->_fromEventSpin);
    _pImpl->_fromEvent = _pImpl->_fromEventSpin->value();
    connect(_pImpl->_fromEventSpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	    [&](int event){ _pImpl->_fromEvent = event; });

    _pImpl->_nEventsSpin = new QSpinBox;
    _pImpl->_nEventsSpin->setMinimum(1);
    _pImpl->_nEventsSpin->setSingleStep(1);
    _pImpl->_nEventsSpin->setValue(1);
    auto nEventsLabel = new QLabel{"# of events:"};
    layout->addWidget(nEventsLabel);
    layout->addWidget(_pImpl->_nEventsSpin);
    _pImpl->_nEvents = _pImpl->_nEventsSpin->value();
    connect(_pImpl->_fromEventSpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	    [&](int event){ _pImpl->_nEventsSpin->setMaximum(_pImpl->_dataHandler->nRawEvents() - _pImpl->_fromEvent); });
    
    _pImpl->_runButton = new QPushButton{"Run"};
    layout->addWidget(_pImpl->_runButton);
    connect(_pImpl->_runButton, &QPushButton::clicked, this, &ReconstructionDock::run);
    _pImpl->_showEventButton = new QPushButton{"Show event"};
    layout->addWidget(_pImpl->_showEventButton);
    connect(_pImpl->_showEventButton, &QPushButton::clicked, this, &ReconstructionDock::showEvent);
    layout->addStretch();
    
    auto widget = new QWidget{};
    widget->setLayout(layout);
    setWidget(widget);
  }

  void ReconstructionDock::loadPadplane()
  {
    QFileDialog dialog{this};
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Padplane geometry (*.geom)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec())
    {
      _pImpl->_state->state()->setPadplane(std::make_unique<Padplane>(dialog.selectedFiles().front().toStdString()));
    }
    else
    {
      std::cout << "> ReconstructionDock::load, message: a padplane geometry file (.geom) must be selected\n";
    }
  }

  void ReconstructionDock::showPadplane()
  {
    if (_pImpl->_state->state()->padplane() != nullptr)
    {
      display(_pImpl->_mainWindow->padPlaneDisplay(), _pImpl->_state->state()->padplane());
    }
    else
    {
      std::cout << "> ReconstructionDock::show, message: a padplane geometry file (.geom) must be loaded first\n";
    }
  }

  void ReconstructionDock::loadTpc()
  {
    QFileDialog dialog{this};
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("TPC geometry (*.geom)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec())
    {
      _pImpl->_state->state()->setTpc(std::make_unique<Tpc>(dialog.selectedFiles().front().toStdString()));
    }
    else
    {
      std::cout << "> ReconstructionDock::load, message: a TPC geometry file (.geom) must be selected\n";
    }
  }

  void ReconstructionDock::showTpc()
  {
    if (_pImpl->_state->state()->tpc() != nullptr)
    {
      display(_pImpl->_mainWindow->tpcDisplay(), _pImpl->_state->state()->tpc());
    }
    else
    {
      std::cout << "> ReconstructionDock::show, message: a TPC geometry file (.geom) must be loaded first\n";
    }
  }

  void ReconstructionDock::loadData()
  {
    QFileDialog dialog{this};
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Raw data file (*.h5)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec())
    {
      auto dataFile = dialog.selectedFiles().front().toStdString();

      _pImpl->_dataHandler->setDataFile(dataFile);
      _pImpl->_dataHandler->open(dataFile);

      // Initialize spin box values
      _pImpl->_fromEventSpin->setMinimum(_pImpl->_dataHandler->fRawEvent());
      _pImpl->_fromEventSpin->setMaximum(_pImpl->_dataHandler->fRawEvent() + _pImpl->_dataHandler->nRawEvents() - 1);
      _pImpl->_fromEventSpin->setValue(_pImpl->_dataHandler->fRawEvent());
      _pImpl->_nEventsSpin->setMaximum(_pImpl->_dataHandler->nRawEvents());
    }
    else
    {
      std::cout << "> ReconstructionDock::load, message: a raw data file (.h5) must be selected\n";
    }
  }

  void ReconstructionDock::run()
  {
    // Check pre-conditions
    if (_pImpl->_state->state()->padplane() == nullptr)
    {
      std::cout << "> ReconstructionDock::run, message: a padplane geometry file (.geom) must be loaded first\n";
      return;
    }
    if (_pImpl->_state->state()->tpc() == nullptr)
    {
      std::cout << "> ReconstructionDock::run, message: a TPC geometry file (.geom) must be loaded first\n";
      return;
    }
    if (_pImpl->_dataHandler->dataFile().empty() )  
    {
      std::cout << "> ReconstructionDock::run, message: a raw data file (.h5) must be loaded first\n";
      return;
    }

    _pImpl->_nEvents = _pImpl->_nEventsSpin->value(); // Get value directly from spinbox, not via value changed slot
    _pImpl->_pTask = std::make_unique<ReconstructionTask>(_pImpl->_dataHandler.get(),
							  static_cast<std::size_t>(_pImpl->_fromEvent),
							  static_cast<std::size_t>(_pImpl->_nEvents),
							  _pImpl->_state.get());
    _pImpl->_pFuture = std::make_unique<QFuture<void> >(QtConcurrent::run(_pImpl->_pTask.get(), &ReconstructionTask::run));

    _pImpl->_pWatcher = std::make_unique<QFutureWatcher<void> >();
    auto pWatcher = _pImpl->_pWatcher.get();
    connect(pWatcher, &QFutureWatcher<void>::started, _pImpl->_mainWindow, &MainWindow::spinTaskStatusWheel);
    connect(pWatcher, &QFutureWatcher<void>::finished, _pImpl->_mainWindow, &MainWindow::stopTaskStatusWheel);
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_loadPadplaneButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_showPadplaneButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_loadTpcButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_showTpcButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_loadDataButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_runButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::started, [&](){ _pImpl->_showEventButton->setEnabled(false); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_loadPadplaneButton->setEnabled(true); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_showPadplaneButton->setEnabled(true); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_loadTpcButton->setEnabled(true); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_showTpcButton->setEnabled(true); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_loadDataButton->setEnabled(true); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_runButton->setEnabled(true); });
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){ _pImpl->_showEventButton->setEnabled(true); });
      
    connect(pWatcher, &QFutureWatcher<void>::finished, [&](){
	_pImpl->_pTask.reset(nullptr);
	_pImpl->_pFuture.reset(nullptr);
	_pImpl->_pWatcher.reset(nullptr);

	// Set number of requested events to actual number of processed events
	// Can happen to be different because of empty events
	_pImpl->_nEvents = _pImpl->_state->state()->events().size();
      });
      
    _pImpl->_pWatcher->setFuture(*(_pImpl->_pFuture.get()));
  }

  void ReconstructionDock::showEvent()
  {
    auto idx = 0;
    if (_pImpl->_nEvents) idx = --_pImpl->_nEvents;

    std::cout << "> display event:\n";
    std::cout << "> .. event id: " << _pImpl->_state->state()->events()[idx].id() << ", idx: " << idx << "/" << _pImpl->_state->state()->events().size() << '\n';

    display(_pImpl->_mainWindow->padPlaneDisplay(), _pImpl->_state->state()->events()[idx], _pImpl->_state->state()->padplane());
    display(_pImpl->_mainWindow->tpcDisplay(), _pImpl->_state->state()->events()[idx], _pImpl->_state->state()->tpc());
  }


  
}
