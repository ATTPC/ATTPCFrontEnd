#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <QtWidgets/QWidget>

#include <memory>

namespace attpcfe {

  class Display : public QWidget { // Could inherit from QOpenGLWidget

    Q_OBJECT
    
    class DisplayImpl;
    std::unique_ptr<DisplayImpl, void(*)(DisplayImpl*)> _pImpl;
    
  public:
    Display(QWidget* parent);

  public slots:
    //void displayPadPlane();
  };

  //class PadPlane;
  //void draw(PadPlane* padPlane, ChartView* chartView) {};
}
#endif
