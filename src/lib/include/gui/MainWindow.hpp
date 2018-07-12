#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include <memory>

namespace attpcfe {

  class GuiState;
  class Display;
  class MainWindow : public QMainWindow {

    Q_OBJECT
    
    class MainWindowImpl;
    std::unique_ptr<MainWindowImpl, void(*)(MainWindowImpl*)> _pImpl;

  private:
    void initMenuBar();
    void initCentralWidget();
    void initStatusBar();
    void initDocks();
    void writeSettings();
    void readSettings();

  protected:
    void closeEvent(QCloseEvent* event) override;

  public:
    MainWindow();
    MainWindow(MainWindow const&) = delete;
    MainWindow& operator=(MainWindow const&) = delete;

    GuiState* state();	
    Display* planeDisplay();
    Display* tpcDisplay();			   

  public slots:
    void spinTaskStatusWheel();
    void stopTaskStatusWheel();
  };
}
#endif
