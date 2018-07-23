#define RECONSTRUCTIONDOCK_CPP
#include <gui/ReconstructionDock.hpp>
#include <gui/ReconstructionDockState.hpp>
#include <gui/ReconstructionDockTasks.hpp>
#include <gui/MainWindow.hpp>
#include <gui/DisplayFunctions.hpp>
#include <core/ReconstructionState.hpp>
#include <core/Padplane.hpp>
#include <core/Tpc.hpp>

#include <QtWidgets/QPushButton>
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
    std::string _rawDataFile;
    
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

    // ReconstructionState held by ReconstructionDock
    std::unique_ptr<ReconstructionDockState> _state{std::make_unique<ReconstructionDockState>()};
  };

  ReconstructionDock::ReconstructionDock(QWidget* parent) : QDockWidget{parent}, _pImpl{new ReconstructionDockImpl{parent}, [](ReconstructionDockImpl* ptr){ delete ptr; }}
  {
    setWindowTitle(tr("Reconstruction"));
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setFixedSize(200, 200);

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
    _pImpl->_runButton = new QPushButton{"Run"};
    layout->addWidget(_pImpl->_runButton);
    connect(_pImpl->_runButton, &QPushButton::clicked, this, &ReconstructionDock::run);
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
      _pImpl->_rawDataFile = dialog.selectedFiles().front().toStdString();
    }
    else
    {
      std::cout << "> ReconstructionDock::load, message: a raw data file (.h5) must be selected\n";
    }
  }

  void ReconstructionDock::run()
  {
    if (!_pImpl->_rawDataFile.empty() )
    {
      _pImpl->_pTask = std::make_unique<ReconstructionTask>(_pImpl->_rawDataFile, _pImpl->_state.get());
      _pImpl->_pFuture = std::make_unique<QFuture<void> >(QtConcurrent::run(_pImpl->_pTask.get(), &ReconstructionTask::run));

      _pImpl->_pWatcher = std::make_unique<QFutureWatcher<void> >();
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::started, _pImpl->_mainWindow, &MainWindow::spinTaskStatusWheel);
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, _pImpl->_mainWindow, &MainWindow::stopTaskStatusWheel);
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::started, [&](){ _pImpl->_loadDataButton->setEnabled(false); });
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::started, [&](){ _pImpl->_runButton->setEnabled(false); });
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, [&](){ _pImpl->_loadDataButton->setEnabled(true); });
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, [&](){ _pImpl->_runButton->setEnabled(true); });
      
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, [&](){
	  _pImpl->_pTask.reset(nullptr);
	  _pImpl->_pFuture.reset(nullptr);
	  _pImpl->_pWatcher.reset(nullptr); });
      
      _pImpl->_pWatcher->setFuture(*(_pImpl->_pFuture.get()));
    }
    else
    {
      std::cout << "> ReconstructionDock::run, message: a raw data file (.h5) file must be loaded first\n";
    }
  }
  
}
