#include <gui/MainWindow.hpp>
#include <QtWidgets/QApplication>
#include <QtGui/QSurfaceFormat>

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("LBNL");
  QCoreApplication::setApplicationName("ATTPC");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QSurfaceFormat format;
  format.setSamples(2);
  QSurfaceFormat::setDefaultFormat(format);

  attpcfe::MainWindow mainWindow;
  mainWindow.show();
  
  return app.exec();
}
