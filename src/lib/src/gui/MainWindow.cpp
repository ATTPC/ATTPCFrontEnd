#define MAINWINDOW_CPP
#include <gui/MainWindow.hpp>
#include <gui/Display.hpp>
#include <gui/ReconstructionDock.hpp>
#include <gui/GuiState.hpp>

//#include <QtWidgets> // Includes QtWidgets, QtGui and QtCore
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QLabel>
#include <QtGui/QMovie>
#include <QtGui/QCloseEvent>
#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>

namespace attpcfe {

  class MainWindow::MainWindowImpl {
    
  public:
    MainWindowImpl() = default; 
    
    // Handles to widgets MainWindow took ownership of
    //QTabWidget _pDisplayTabs{nullptr};
    Display* _pPadplaneDisplay{nullptr};
    Display* _pTpcDisplay{nullptr};
    ReconstructionDock* _pReconstructionDock{nullptr};
    QLabel* _pTaskStatus{nullptr};
  };

  MainWindow::MainWindow() : _pImpl{new MainWindowImpl{}, [](MainWindowImpl* ptr){ delete ptr; }}
  {
    setWindowTitle("ATTPC");
    initMenuBar();
    initCentralWidget();
    initDocks();
    initStatusBar();

    // Set geometry for the app window
    readSettings(); 
  }

  void MainWindow::initMenuBar()
  {
    // Initialize the app menu. Dock menus are initialized in initDocks
    menuBar()->setNativeMenuBar(true);
    auto appMenu = menuBar()->addMenu("&Application"); 
    auto exit = appMenu->addAction("&Exit", this, SLOT(close()), QKeySequence::Quit);
    exit->setStatusTip(tr("Close the application"));
  }

  void MainWindow::initCentralWidget()
  {
    //_pImpl->pDisplayTabs = new QTabWidget;
    auto tabs = new QTabWidget;
    
    _pImpl->_pPadplaneDisplay = new Display(this, Display::VIEW_MODE::VIEW_2D);
    tabs->addTab(_pImpl->_pPadplaneDisplay, tr("Padplane"));

    _pImpl->_pTpcDisplay = new Display(this, Display::VIEW_MODE::VIEW_3D);
    tabs->addTab(_pImpl->_pTpcDisplay, tr("TPC"));
    
    setCentralWidget(tabs);
  }

  void MainWindow::initStatusBar()
  {
    statusBar()->showMessage("Ready");
    _pImpl->_pTaskStatus = new QLabel{};
    _pImpl->_pTaskStatus->setMovie(new QMovie{"/home/nico/Downloads/wheel.gif"});
    _pImpl->_pTaskStatus->hide();
    statusBar()->addPermanentWidget(_pImpl->_pTaskStatus, 0);
  }
  
  void MainWindow::initDocks()
  {
    auto dockMenu = menuBar()->addMenu("&Docks");
      
    // Reconstruction dock
    _pImpl->_pReconstructionDock = new ReconstructionDock{this};
    addDockWidget(Qt::RightDockWidgetArea, _pImpl->_pReconstructionDock);
    dockMenu->addAction(_pImpl->_pReconstructionDock->toggleViewAction());
    dockMenu->actions().last()->setStatusTip(tr("View reconstruction dock"));
    dockMenu->actions().last()->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  }

  Display* MainWindow::padPlaneDisplay() { return _pImpl->_pPadplaneDisplay; }
  Display* MainWindow::tpcDisplay() { return _pImpl->_pTpcDisplay; }
  
  void MainWindow::closeEvent(QCloseEvent* event)
  {
    writeSettings();
    event->accept();
  }

  void MainWindow::writeSettings()
  {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
  }

  void MainWindow::readSettings()
  {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty())
    {
      const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
      resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
      move((availableGeometry.width() - width()) / 2,
	   (availableGeometry.height() - height()) / 2);
    }
    else
    {
      restoreGeometry(geometry);
    }    
  }

  void MainWindow::spinTaskStatusWheel()
  {
    statusBar()->showMessage("Running task");
    _pImpl->_pTaskStatus->show();
    _pImpl->_pTaskStatus->movie()->start();
  }
  
  void MainWindow::stopTaskStatusWheel()
  {
    statusBar()->showMessage("");
    _pImpl->_pTaskStatus->movie()->stop();
    _pImpl->_pTaskStatus->hide();
  }
  
}
