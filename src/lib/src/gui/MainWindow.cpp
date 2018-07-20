#define MAINWINDOW_CPP
#include <gui/MainWindow.hpp>
#include <gui/Display.hpp>
#include <gui/PadplaneDock.hpp>
#include <gui/TpcDock.hpp>
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
    MainWindowImpl() : _pState{std::make_unique<GuiState>()} {} 

    std::unique_ptr<GuiState> _pState;
    
    // Handles to widgets MainWindow took ownership of
    Display* _pPadplaneDisplay{nullptr};
    Display* _pTpcDisplay{nullptr};
    PadplaneDock* _pPadplaneDock{nullptr};
    TpcDock* _pTpcDock{nullptr};
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
    auto tabs = new QTabWidget;
    //There is a frame appearing around the widgets placed in tabs, did not figure out how to get rid of it yet.
    //tabs->setStyleSheet("background:QRgb(0xd2d0d1);");
    
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
      
    // Padplane dock
    _pImpl->_pPadplaneDock = new PadplaneDock{this};
    addDockWidget(Qt::RightDockWidgetArea, _pImpl->_pPadplaneDock);
    //_pImpl->_pPadplaneDock->hide();
    dockMenu->addAction(_pImpl->_pPadplaneDock->toggleViewAction());
    dockMenu->actions().last()->setStatusTip(tr("View padplane dock"));
    dockMenu->actions().last()->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));

    // TPC dock
    _pImpl->_pTpcDock = new TpcDock{this};
    addDockWidget(Qt::RightDockWidgetArea, _pImpl->_pTpcDock);
    dockMenu->addAction(_pImpl->_pTpcDock->toggleViewAction());
    dockMenu->actions().last()->setStatusTip(tr("View TPC dock"));
    dockMenu->actions().last()->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
  }

  GuiState* MainWindow::state() { return _pImpl->_pState.get(); }
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
