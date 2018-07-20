#ifndef PADPLANEDOCK_HPP
#define PADPLANEDOCK_HPP

#include <QtWidgets/QDockWidget>

#include <memory>

namespace attpcfe {

  class PadplaneDock : public QDockWidget {

    Q_OBJECT

    class PadplaneDockImpl;
    std::unique_ptr<PadplaneDockImpl, void(*)(PadplaneDockImpl*)> _pImpl;

  public:
    PadplaneDock(QWidget* parent);

    public slots:
    void load();
    void show();
  };
}
#endif
