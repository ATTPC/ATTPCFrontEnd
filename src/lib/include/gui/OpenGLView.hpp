#ifndef OPENGLVIEW_HPP
#define OPENGLVIEW_HPP

#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

#include <memory>

namespace attpcfe {

  class OpenGLView : public QOpenGLWidget, protected QOpenGLFunctions {

    Q_OBJECT

    class OpenGLViewImpl;
    std::unique_ptr<OpenGLViewImpl, void(*)(OpenGLViewImpl*)> _pImpl;
    
  public:
    OpenGLView(QWidget* parent = nullptr);
    ~OpenGLView();
  };
}
#endif
