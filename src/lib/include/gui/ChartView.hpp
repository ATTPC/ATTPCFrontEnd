#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <QtCharts/QChartView>
using namespace QtCharts;

#include <memory>

namespace attpcfe {

  class MainWindow;
  class ChartView : public QChartView {

    class ChartViewImpl;
    std::unique_ptr<ChartViewImpl, void(*)(ChartViewImpl*)> _pImpl;
    
  protected:
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    
  public:
    ChartView(QChart* chart, MainWindow* mainWindow);
    //void drawMap();
  };
}
#endif
