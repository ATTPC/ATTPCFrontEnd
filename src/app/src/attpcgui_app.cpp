#include <gui/MainWindow.hpp>
#include <QtWidgets/QApplication>
#include <QtGui/QSurfaceFormat>

#include <QVTKOpenGLWidget.h>

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("LBNL");
  QCoreApplication::setApplicationName("ATTPC");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  //QSurfaceFormat format;
  //format.setSamples(4);
  //QSurfaceFormat::setDefaultFormat(format);

  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  attpcfe::MainWindow mainWindow;
  mainWindow.show();
  
  return app.exec();
}
