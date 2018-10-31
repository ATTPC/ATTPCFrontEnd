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

  void display(Display* pDisplay, Tpc* pTpc)
  {
    auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(20);
    cylinder->SetCenter(0., 0., 0.);
    cylinder->SetRadius(pTpc->radius());
    cylinder->SetHeight(pTpc->height());
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

    pDisplay->renderer()->AddActor(cylinderActor);

    pDisplay->renderer()->ResetCamera();
    pDisplay->renderer()->GetActiveCamera()->Zoom(1.5);

    pDisplay->renderer()->Render();
  }

  void display(Display* pDisplay, Event const& event, Padplane* pPadplane)
  {
    if (event.nHitLists() == 0)
    {
      std::cout << "> DisplayFunctions::display, message: current event has no hits\n";
      return;
    }

    // First need to clear display from previous event.
    for (auto& litPad : pPadplane->litPads())
    {
      auto idx = pDisplay->chart()->GetPlotIndex(litPad);
      pDisplay->chart()->RemovePlot(idx);
    }
    pPadplane->litPads().clear();

    // We asssume a single hit per list for now.
    auto maxCharge = 0.;
    for (auto const& hitList : event.hitLists())
    {
      if (hitList.hits()[0].charge() > maxCharge) maxCharge = hitList.hits()[0].charge();
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

      // We need the current pad coordinates only once, so look only at first hit in hitlist.
      Hit const& hit = hitList.hits()[0];
      auto padNum = hit.padNum();

      auto x_0 = hit.position()[0] - pPadplane->padSize(padNum) / 2;
      auto x_1 = hit.position()[0];
      auto x_2 = hit.position()[0] + pPadplane->padSize(padNum) / 2;
      auto y_0 = (pPadplane->padIsUp(padNum)) ?
	hit.position()[1] - pPadplane->padHeight(padNum) / 2 :
	hit.position()[1] + pPadplane->padHeight(padNum) / 2;
      auto y_1 = (pPadplane->padIsUp(padNum)) ?
	hit.position()[1] + pPadplane->padHeight(padNum) / 2 :
	hit.position()[1] - pPadplane->padHeight(padNum) / 2;
      //auto y_2 = y_0;
      auto y_2 = (pPadplane->padIsUp(padNum)) ?
	hit.position()[1] - pPadplane->padHeight(padNum) / 2 :
	hit.position()[1] + pPadplane->padHeight(padNum) / 2;
	
      table->SetValue(0, 0, x_0);
      table->SetValue(1, 0, x_1);
      table->SetValue(2, 0, x_2);
      table->SetValue(3, 0, x_0);
      table->SetValue(0, 1, y_0);
      table->SetValue(1, 1, y_1);
      table->SetValue(2, 1, y_2);
      table->SetValue(3, 1, y_0);

      auto linePlot = pDisplay->chart()->AddPlot(vtkChart::LINE);
      pPadplane->litPads().push_back(linePlot);
      linePlot->SetInputData(table, 0, 1);

      double ratio = hit.charge() / maxCharge;
      double red = 255 * ratio;
      double green = (ratio <= 0.5) ? 255 * 2 * ratio : 255 * (1. - 2 * (ratio - 1.));
      double blue = 255 * (1. - ratio);
      linePlot->SetColor(red, green, blue, 255);
    }
  }

  void display(Display* pDisplay, Event const& event, Tpc* pTpc)
  {
    if (event.nHitLists() == 0)
    {
      std::cout << "> DisplayFunctions::display, message: current event has no hits\n";
      return;
    }

    // First need to clear display from previous event.
    pDisplay->renderer()->RemoveAllViewProps(); // Need to check for leaks here.
    display(pDisplay, pTpc);

    auto maxCharge = 0.;
    for (auto const& hitList : event.hitLists())
    {
      if (hitList.hits()[0].charge() > maxCharge) maxCharge = hitList.hits()[0].charge();
    }
      
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
	cubeActor->GetProperty()->SetOpacity(0.5);

	double ratio = hit.charge() / maxCharge;
	double red = ratio;
	double green = (ratio <= 0.5) ? 2 * ratio : 1. - 2 * (ratio - 1.);
	double blue = 1. - ratio;
	cubeActor->GetProperty()->SetColor(red, blue, green);

	//cubeActor->RotateX(-20.0); 
	//cubeActor->RotateZ(-20.0); 

	pDisplay->renderer()->AddActor(cubeActor);
      }
    }

    //pDisplay->renderer()->Render();
  }

}
