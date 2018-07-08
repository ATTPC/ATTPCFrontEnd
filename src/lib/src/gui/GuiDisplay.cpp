#define GUIDISPLAY_CPP
#include <gui/GuiDisplay.hpp>
#include <gui/GuiChartView.hpp>

#include <QtWidgets/QVBoxLayout>

using namespace QtCharts;

namespace attpcfe {

  class GuiDisplay::GuiDisplayImpl {

  public:
    GuiDisplayImpl() {}

    // Handles to widgets GuiDisplay took ownership of
    GuiChartView* _chartView;
  };
  
  GuiDisplay::GuiDisplay(QWidget* parent) : QWidget{parent}, _pImpl{new GuiDisplayImpl{}, [](GuiDisplayImpl* ptr){ delete ptr; }}
  {
    setAutoFillBackground(false);
    setLayout(new QVBoxLayout{});
    
    _pImpl->_chartView = new GuiChartView{new QChart{}};
    layout()->addWidget(_pImpl->_chartView);
  }

  //void GuiDisplay::displayMap()
  //{
  //  _pImpl->_chartView->drawMap();
  //}
}
