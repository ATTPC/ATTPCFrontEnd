#ifndef GUIDISPLAY_HPP
#define GUIDISPLAY_HPP

#include <QtWidgets/QWidget>

#include <memory>

namespace attpcfe {

  class GuiDisplay : public QWidget { // Could inherit from QOpenGLWidget

    Q_OBJECT
    
    class GuiDisplayImpl;
    std::unique_ptr<GuiDisplayImpl, void(*)(GuiDisplayImpl*)> _pImpl;
    
  public:
    GuiDisplay(QWidget* parent);

  public slots:
    //void displayMap();
  };
}
#endif
