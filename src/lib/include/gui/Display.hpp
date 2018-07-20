#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <QtWidgets/QWidget>

#include <memory>

class vtkContextView;
class vtkChartXY;
class vtkGenericOpenGLRenderWindow;
class vtkRenderer;

namespace attpcfe {

  class Display : public QWidget { 

    Q_OBJECT
    
    class DisplayImpl;
    std::unique_ptr<DisplayImpl, void(*)(DisplayImpl*)> _pImpl;
    
  public:
    // Seems that moc cannot parse enum class, or at least the { construct ?
    //MOC_SKIP_BEGIN
    enum class VIEW_MODE { VIEW_2D, VIEW_3D };
    //MOC_SKIP_END
    
    Display(QWidget* parent, VIEW_MODE mode);

    //public slots:

    vtkContextView* view();
    vtkChartXY* chart();
    vtkGenericOpenGLRenderWindow* renderWindow();
    vtkRenderer* renderer();
  };

}
#endif
