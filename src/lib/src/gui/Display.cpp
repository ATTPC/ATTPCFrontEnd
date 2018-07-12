#define DISPLAY_CPP
#include <gui/Display.hpp>
#include <gui/MainWindow.hpp>
#include <gui/ChartView.hpp>
#include <gui/OpenGLView.hpp>

#include <QtWidgets/QVBoxLayout>

using namespace QtCharts;

namespace attpcfe {

  class Display::DisplayImpl {

  public:
    DisplayImpl(QWidget* parent) : _pMainWindow{dynamic_cast<MainWindow*>(parent)} {}

    MainWindow* _pMainWindow;

    // Handles to widgets GuiDisplay took ownership of
    std::variant<ChartView*, OpenGLView*> _view;
  };
  
  Display::Display(QWidget* parent, VIEW_MODE mode) : QWidget{parent}, _pImpl{new DisplayImpl{parent}, [](DisplayImpl* ptr){ delete ptr; }}
  {  
    setLayout(new QVBoxLayout{});
    
    if (mode == VIEW_MODE::VIEW_2D)
    {
      _pImpl->_view = new ChartView{new QChart{}, _pImpl->_pMainWindow};
      layout()->addWidget(std::get<ChartView*>(_pImpl->_view));
    }

    if (mode == VIEW_MODE::VIEW_3D)
    {
      _pImpl->_view = new OpenGLView; 
      layout()->addWidget(std::get<OpenGLView*>(_pImpl->_view));
    }
  }

}
