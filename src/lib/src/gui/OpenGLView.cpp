#define OPENGLVIEW_CPP
#include <gui/OpenGLView.hpp>

namespace attpcfe {

  class OpenGLView::OpenGLViewImpl {

  public:
    OpenGLViewImpl() {}
  };

  OpenGLView::OpenGLView(QWidget* parent) :
    QOpenGLWidget{parent}, _pImpl{new OpenGLViewImpl{}, [](OpenGLViewImpl* ptr){ delete ptr; }} {}

  OpenGLView::~OpenGLView() {}
}
