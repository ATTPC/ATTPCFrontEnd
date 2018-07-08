#include <gui/GuiMainWindow.hpp>
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

  attpcfe::GuiMainWindow MainWindow;
  MainWindow.show();
  
  return app.exec();
}
