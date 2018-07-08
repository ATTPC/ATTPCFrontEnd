#define GUIMAINWINDOW_CPP
#include <gui/GuiMainWindow.hpp>
#include <gui/GuiDisplay.hpp>
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

  class GuiMainWindow::GuiMainWindowImpl {
    
  public:
    GuiMainWindowImpl() {} 

    // Handles to widgets GuiMainWindow took ownership of
    GuiDisplay* _display{nullptr};
    //GuiMapParser* _mapParser{nullptr};
    QLabel* _taskStatus{nullptr};
  };

  GuiMainWindow::GuiMainWindow() : _pImpl{new GuiMainWindowImpl{}, [](GuiMainWindowImpl* ptr){ delete ptr; }}
  {
    setWindowTitle("ATTPC");
    initMenuBar();
    initCentralWidget();
    initDocks();
    initStatusBar();

    // Set geometry for the app window
    readSettings(); 
  }

  void GuiMainWindow::initMenuBar()
  {
    // Initialize the app menu. Dock menus are initialized in initDocks
    menuBar()->setNativeMenuBar(true);
    auto appMenu = menuBar()->addMenu("&Application"); 
    auto exit = appMenu->addAction("&Exit", this, SLOT(close()), QKeySequence::Quit);
    exit->setStatusTip(tr("Close the application"));
  }

  void GuiMainWindow::initCentralWidget()
  {
    _pImpl->_display = new GuiDisplay{this};
    setCentralWidget(_pImpl->_display);
  }

  void GuiMainWindow::initStatusBar()
  {
    statusBar()->showMessage("Ready");
    _pImpl->_taskStatus = new QLabel{};
    _pImpl->_taskStatus->setMovie(new QMovie{"/home/nico/Downloads/wheel.gif"});
    _pImpl->_taskStatus->hide();
    statusBar()->addPermanentWidget(_pImpl->_taskStatus, 0);
  }
  
  void GuiMainWindow::initDocks()
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

  GuiDisplay* GuiMainWindow::display() { return _pImpl->_display; }

  void GuiMainWindow::closeEvent(QCloseEvent* event)
  {
    writeSettings();
    event->accept();
  }

  void GuiMainWindow::writeSettings()
  {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
  }

  void GuiMainWindow::readSettings()
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

  void GuiMainWindow::spinTaskStatusWheel()
  {
    statusBar()->showMessage("Running task");
    _pImpl->_taskStatus->show();
    _pImpl->_taskStatus->movie()->start();
  }
  
  void GuiMainWindow::stopTaskStatusWheel()
  {
    statusBar()->showMessage("");
    _pImpl->_taskStatus->movie()->stop();
    _pImpl->_taskStatus->hide();
  }
  
}
