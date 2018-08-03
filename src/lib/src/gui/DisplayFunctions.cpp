#define DISPLAYFUNCTIONS_CPP
#include <gui/DisplayFunctions.hpp>
#include <gui/Display.hpp>
#include <core/Padplane.hpp>
#include <core/Tpc.hpp>
#include <core/Event.hpp>
#include <core/HitList.hpp>
#include <core/Hit.hpp>

#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkSmartPointer.h>
#include <vtkTable.h>
#include <vtkDoubleArray.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkCylinderSource.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include <fstream>
#include <sstream>

#include <iostream>
#include <vtkPropCollection.h>

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
    cylinderActor->GetProperty()->SetOpacity(0.1);
    cylinderActor->RotateX(-90.0); // Points to the right
    //cylinderActor->RotateZ(-20.0); // Points to the top

    
    display->renderer()->AddActor(cylinderActor);

    display->renderer()->ResetCamera();
    display->renderer()->GetActiveCamera()->Zoom(1.5);
  }

  void display(Display* display, Event const& event, Padplane* padplane)
  {
    if (event.nHitLists() == 0)
    {
      std::cout << "> DisplayFunctions::display, message: current event has no hits\n";
      return;
    }

    for (auto const& hitList : event.hitLists())
    {
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

      // need pad coordinates only once, so look only at first hit in hitlist
      Hit const& hit = hitList.hits()[0];
      auto padNum = hit.padNum();

      auto x_0 = hit.position()[0] - padplane->padSize(padNum) / 2;
      auto x_1 = hit.position()[0];
      auto x_2 = hit.position()[0] + padplane->padSize(padNum) / 2;
      auto y_0 = (padplane->padIsUp(padNum)) ?
	hit.position()[1] - padplane->padHeight(padNum) / 2 :
	hit.position()[1] + padplane->padHeight(padNum) / 2;
      auto y_1 = (padplane->padIsUp(padNum)) ?
	hit.position()[1] + padplane->padHeight(padNum) / 2 :
	hit.position()[1] - padplane->padHeight(padNum) / 2;
      //auto y_2 = y_0;
      auto y_2 = (padplane->padIsUp(padNum)) ?
	hit.position()[1] - padplane->padHeight(padNum) / 2 :
	hit.position()[1] + padplane->padHeight(padNum) / 2;
	
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
      linePlot->SetColor(255, 0, 0, 255);
    }
  }

  void display(Display* display, Event const& event, Tpc* tpc)
  {
    if (event.nHitLists() == 0)
    {
      std::cout << "> DisplayFunctions::display, message: current event has no hits\n";
      return;
    }

    // First need to clear display from previous event.
    display->renderer()->RemoveAllViewProps(); // Need to check for leaks here.
    display->renderer()->Render();
      
    for (auto const& hitList : event.hitLists())
    {
      for (const auto& hit : hitList.hits())
      {
	auto cube = vtkSmartPointer<vtkCubeSource>::New();
	cube->SetXLength(1.0);
	cube->SetYLength(1.0);
	cube->SetZLength(1.0);
	cube->SetCenter(hit.position()[0] / 10, hit.position()[1] / 10, hit.position()[2] / 10); // cm

	auto cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cube->GetOutputPort());

	auto cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
	cubeActor->GetProperty()->SetOpacity(0.5);

	//cubeActor->RotateX(-20.0); 
	//cubeActor->RotateZ(-20.0); 

	display->renderer()->AddActor(cubeActor);
      }
    }	
  }

}
