#define DISPLAY_CPP
#include <gui/Display.hpp>
#include <gui/MainWindow.hpp>
#include <gui/ChartView.hpp>
#include <gui/OpenGLView.hpp>

#include <QtWidgets/QVBoxLayout>

#include <QVTKOpenGLWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkChartXY.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>

namespace attpcfe {

  class Display::DisplayImpl {

  public:
    DisplayImpl(QWidget* parent) : _pMainWindow{dynamic_cast<MainWindow*>(parent)} {}

    MainWindow* _pMainWindow;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> _pRenderWindow{vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()};
    vtkSmartPointer<vtkContextView> _pView;
    vtkSmartPointer<vtkChartXY> _pChart;
    vtkSmartPointer<vtkRenderer> _pRenderer;

    // Handles to widgets GuiDisplay took ownership of
    QVTKOpenGLWidget* _pVtkWidget{nullptr};
  };
  
  Display::Display(QWidget* parent, VIEW_MODE mode) : QWidget{parent}, _pImpl{new DisplayImpl{parent}, [](DisplayImpl* ptr){ delete ptr; }}
  {  
    setLayout(new QVBoxLayout{});

    _pImpl->_pVtkWidget = new QVTKOpenGLWidget{this};
    _pImpl->_pVtkWidget->SetRenderWindow(_pImpl->_pRenderWindow.Get());
    layout()->addWidget(_pImpl->_pVtkWidget);

    if (mode == VIEW_MODE::VIEW_2D)
    {
      _pImpl->_pView = vtkSmartPointer<vtkContextView>::New();
      _pImpl->_pView->SetRenderWindow(_pImpl->_pRenderWindow.Get());
      _pImpl->_pView->SetInteractor(_pImpl->_pRenderWindow->GetInteractor());
      _pImpl->_pView->GetInteractor()->Initialize();

      _pImpl->_pChart = vtkSmartPointer<vtkChartXY>::New();
      _pImpl->_pView->GetScene()->AddItem(_pImpl->_pChart);
    }

    if (mode == VIEW_MODE::VIEW_3D)
    {
      _pImpl->_pRenderer = vtkSmartPointer<vtkRenderer>::New();
      _pImpl->_pRenderer->SetBackground(1., 1., 1.);
      //_pImpl->_pRenderer->ResetCamera();
      //_pImpl->_pRenderer->GetActiveCamera()->Zoom(1.5);
      _pImpl->_pVtkWidget->GetRenderWindow()->AddRenderer(_pImpl->_pRenderer.Get());

      /*
      auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
      cylinder->SetResolution(20);
      cylinder->SetCenter(0., 0., 0.);
      cylinder->SetRadius(25.);
      cylinder->SetHeight(100.);
      cylinder->SetCapping(true);

      // The mapper is responsible for pushing the geometry into the graphics library.
      // It may also do color mapping, if scalars or other attributes are defined.
      auto cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

      // The actor is a grouping mechanism: besides the geometry (mapper), it
      // also has a property, transformation matrix, and/or texture map.
      auto cylinderActor = vtkSmartPointer<vtkActor>::New();
      cylinderActor->SetMapper(cylinderMapper);
      cylinderActor->GetProperty()->SetColor(0.450, 0.450, 0.450);
      cylinderActor->GetProperty()->SetOpacity(0.2);
      cylinderActor->RotateX(-75.0); 
      cylinderActor->RotateZ(-35.0); // Maps to Y
    
      // The renderer generates the image which is then displayed on the render window.
      // It can be thought of as a scene to which the actor is added
      auto renderer = vtkSmartPointer<vtkRenderer>::New();
      renderer->AddActor(cylinderActor);
      renderer->SetBackground(1., 1., 1.);
      renderer->ResetCamera();
      renderer->GetActiveCamera()->Zoom(1.5);

      _pImpl->_pVtkWidget->GetRenderWindow()->AddRenderer(renderer.Get());
      */
    } 
  }

  vtkContextView* Display::view()
  {
    return _pImpl->_pView.Get();
  }

  vtkChartXY* Display::chart()
  {
    return _pImpl->_pChart.Get();
  }

  vtkGenericOpenGLRenderWindow* Display::renderWindow()
  {
    return _pImpl->_pRenderWindow.Get();
  }

  vtkRenderer* Display::renderer()
  {
    return _pImpl->_pRenderer.Get();
  }

}
