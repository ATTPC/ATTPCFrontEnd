#define MAINWINDOW_CPP
#include <gui/MainWindow.hpp>
#include <gui/Display.hpp>
#include <gui/GuiState.hpp>
//#include <GuiMapParser.hpp>

//#include <QtWidgets> // Includes QtWidgets, QtGui and QtCore
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMenuBar>
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
    Display* _pDisplay{nullptr};
    //GuiMapParser* _mapParser{nullptr};
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
    _pImpl->_pDisplay = new Display{this};
    setCentralWidget(_pImpl->_pDisplay);
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

    // Map parser
    //_pImpl->_mapParser = new GuiMapParser{this};
    //addDockWidget(Qt::RightDockWidgetArea, _pImpl->_mapParser);
    //_pImpl->_mapParser->hide();
    //dockMenu->addAction(_pImpl->_mapParser->toggleViewAction());
    //dockMenu->actions().last()->setStatusTip(tr("View map parser"));
    //dockMenu->actions().last()->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));

    // Next dock
  }

  GuiState* MainWindow::state() { return _pImpl->_pState.get(); }
  Display* MainWindow::display() { return _pImpl->_pDisplay; }

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