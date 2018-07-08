#ifndef GUIMAINWINDOW_HPP
#define GUIMAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include <memory>

namespace attpcfe {

  class GuiDisplay;
  class GuiMainWindow : public QMainWindow {

    Q_OBJECT
    
    class GuiMainWindowImpl;
    std::unique_ptr<GuiMainWindowImpl, void(*)(GuiMainWindowImpl*)> _pImpl;

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
    GuiMainWindow();
    GuiMainWindow(GuiMainWindow const&) = delete;
    GuiMainWindow& operator=(GuiMainWindow const&) = delete;

    GuiDisplay* display();							   

  public slots:
    void spinTaskStatusWheel();
    void stopTaskStatusWheel();
  };
}
#endif
