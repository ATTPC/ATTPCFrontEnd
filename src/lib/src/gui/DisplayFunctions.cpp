#define DISPLAYFUNCTIONS_CPP
#include <gui/DisplayFunctions.hpp>
#include <gui/Display.hpp>
#include <reco/Padplane.hpp>
#include <reco/Tpc.hpp>

#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkSmartPointer.h>
#include <vtkTable.h>
#include <vtkDoubleArray.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include <fstream>
#include <sstream>

namespace attpcfe {

  void display(Display* display, Padplane* padplane)
  {      
    std::ifstream in{padplane->geomFile()};

    int padNum;
    double x_0, x_1, x_2;
    double y_0, y_1, y_2;
    std::string line;
    while (std::getline(in, line))
    {
      std::istringstream s{line};
      s >> padNum >> x_0 >> y_0 >> x_1 >> y_1 >> x_2 >> y_2;

      auto table = vtkSmartPointer<vtkTable>::New();
      auto arrx = vtkSmartPointer<vtkDoubleArray>::New();
      arrx->Allocate(4);
      table->AddColumn(arrx);
      auto arry = vtkSmartPointer<vtkDoubleArray>::New();
      arry->Allocate(4);
      table->AddColumn(arry);
      table->GetColumn(0)->SetName("x");
      table->GetColumn(1)->SetName("y");

      table->SetNumberOfRows(4);
      
      table->SetValue(0, 0, x_0);
      table->SetValue(1, 0, x_1);
      table->SetValue(2, 0, x_2);
      table->SetValue(3, 0, x_0);
      table->SetValue(0, 1, y_0);
      table->SetValue(1, 1, y_1);
      table->SetValue(2, 1, y_2);
      table->SetValue(3, 1, y_0);

      auto linePlot = display->chart()->AddPlot(vtkChart::LINE);
      linePlot->SetInputData(table, 0, 1);
      linePlot->SetColor(0, 0, 0, 255);
    }
  }

  void display(Display* display, Tpc* tpc)
  {
    auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(20);
    cylinder->SetCenter(0., 0., 0.);
    cylinder->SetRadius(tpc->radius());
    cylinder->SetHeight(tpc->height());
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
    
    display->renderer()->AddActor(cylinderActor);

    display->renderer()->ResetCamera();
    display->renderer()->GetActiveCamera()->Zoom(1.5);
  }

}
