#ifndef GUICHARTVIEW_HPP
#define GUICHARTVIEW_HPP

#include <QtCharts/QChartView>
using namespace QtCharts;

namespace attpcfe {

  class GuiChartView : public QChartView {

  protected:
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    
  public:
    GuiChartView(QChart* chart);
    //void drawMap();
  };
}
#endif
