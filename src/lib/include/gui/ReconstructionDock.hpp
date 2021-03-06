#ifndef RECONSTRUCTIONDOCK_HPP
#define RECONSTRUCTIONDOCK_HPP

#include <QtWidgets/QDockWidget>

#include <memory>

namespace attpcfe {

  class ReconstructionDock : public QDockWidget {

    Q_OBJECT

    class ReconstructionDockImpl;
    std::unique_ptr<ReconstructionDockImpl, void(*)(ReconstructionDockImpl*)> _pImpl;

  public:
    ReconstructionDock(QWidget* parent);

    public slots:
    void loadPadplane();
    void loadTpc();
    void loadData();
    void showPadplane();
    void showTpc();
    void run();
    void showEvent();
  };
}
#endif
