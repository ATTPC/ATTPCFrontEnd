#define RECONSTRUCTIONDOCK_CPP
#include <gui/ReconstructionDock.hpp>
#include <gui/ReconstructionTasks.hpp>
#include <gui/MainWindow.hpp>

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
    std::unique_ptr<QFutureWatcher<void> > _pWatcher;
    std::unique_ptr<ReconstructionTask> _pTask;
    std::unique_ptr<QFuture<void> > _pFuture;

    // Handles to widgets ReconstructionDock took ownership of
    QPushButton* _loadButton{nullptr};
    QPushButton* _runButton{nullptr};

    // State of ReconstructionDock
    std::string _rawDataFile;
  };

  ReconstructionDock::ReconstructionDock(QWidget* parent) : QDockWidget{parent}, _pImpl{new ReconstructionDockImpl{parent}, [](ReconstructionDockImpl* ptr){ delete ptr; }}
  {
    setWindowTitle(tr("Reconstruction"));
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setFixedSize(200, 200);

    auto layout = new QVBoxLayout{};
    _pImpl->_loadButton = new QPushButton{"Load"};
    layout->addWidget(_pImpl->_loadButton);
    connect(_pImpl->_loadButton, &QPushButton::clicked, this, &ReconstructionDock::load);
    _pImpl->_runButton = new QPushButton{"Run"};
    layout->addWidget(_pImpl->_runButton);
    connect(_pImpl->_runButton, &QPushButton::clicked, this, &ReconstructionDock::run);
    layout->addStretch();
    
    auto widget = new QWidget{};
    widget->setLayout(layout);
    setWidget(widget);
  }

  void ReconstructionDock::load()
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
      _pImpl->_pTask = std::make_unique<ReconstructionTask>();
      _pImpl->_pFuture = std::make_unique<QFuture<void> >(QtConcurrent::run(_pImpl->_pTask.get(), &ReconstructionTask::run));

      _pImpl->_pWatcher = std::make_unique<QFutureWatcher<void> >();
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::started, _pImpl->_mainWindow, &MainWindow::spinTaskStatusWheel);
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, _pImpl->_mainWindow, &MainWindow::stopTaskStatusWheel);
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::started, [&](){ _pImpl->_loadButton->setEnabled(false); });
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::started, [&](){ _pImpl->_runButton->setEnabled(false); });
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, [&](){ _pImpl->_loadButton->setEnabled(true); });
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, [&](){ _pImpl->_runButton->setEnabled(true); });
      
      connect(_pImpl->_pWatcher.get(), &QFutureWatcher<void>::finished, [&](){
	  _pImpl->_pTask.reset(nullptr);
	  _pImpl->_pFuture.reset(nullptr);
	  _pImpl->_pWatcher.reset(nullptr); });
      
      _pImpl->_pWatcher->setFuture(*(_pImpl->_pFuture.get()));
    }
    else
    {
      std::cout << "> ReconstructionDock::run, message: a raw data file (.h) file must be loaded first\n";
    }
  }
  
}
