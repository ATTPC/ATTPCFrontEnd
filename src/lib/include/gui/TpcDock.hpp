#ifndef TPCDOCK_HPP
#define TPCDOCK_HPP

#include <QtWidgets/QDockWidget>

#include <memory>

namespace attpcfe {

  class TpcDock : public QDockWidget {

    Q_OBJECT

    class TpcDockImpl;
    std::unique_ptr<TpcDockImpl, void(*)(TpcDockImpl*)> _pImpl;

  public:
    TpcDock(QWidget* parent);

    public slots:
    void load();
    void show();
  };
}
#endif
