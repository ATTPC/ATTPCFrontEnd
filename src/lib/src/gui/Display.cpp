#define DISPLAY_CPP
#include <gui/Display.hpp>
#include <gui/MainWindow.hpp>
#include <gui/ChartView.hpp>

#include <QtWidgets/QVBoxLayout>

using namespace QtCharts;

namespace attpcfe {

  class Display::DisplayImpl {

  public:
    DisplayImpl(QWidget* parent) : _pMainWindow{dynamic_cast<MainWindow*>(parent)} {}

    MainWindow* _pMainWindow;

    // Handles to widgets GuiDisplay took ownership of
    ChartView* _pChartView;
  };
  
  Display::Display(QWidget* parent) : QWidget{parent}, _pImpl{new DisplayImpl{parent}, [](DisplayImpl* ptr){ delete ptr; }}
  {
    setAutoFillBackground(false);
    setLayout(new QVBoxLayout{});
    
    _pImpl->_pChartView = new ChartView{new QChart{}, _pImpl->_pMainWindow};
    layout()->addWidget(_pImpl->_pChartView);
  }

  //void GuiDisplay::displayMap()
  //{
  //  _pImpl->_chartView->drawMap();
  //}
}
