#define CHARTVIEW_CPP
#include <gui/ChartView.hpp>
#include <gui/MainWindow.hpp>
#include <gui/GuiState.hpp>
//#include <OSMMap.hpp>

#include <QtCharts/QLineSeries>

namespace attpcfe {

  class ChartView::ChartViewImpl {

  public:
    ChartViewImpl(MainWindow* mainWindow) : _pMainWindow{mainWindow} {}

    MainWindow* _pMainWindow;
  };

  ChartView::ChartView(QChart* chart, MainWindow* mainWindow) :
    QChartView{chart}, _pImpl{new ChartViewImpl{mainWindow}, [](ChartViewImpl* ptr){ delete ptr; }}
  {
    // Set some cosmetics
    setRenderHint(QPainter::Antialiasing);
    this->chart()->legend()->hide();
    this->chart()->setBackgroundBrush(QBrush(QRgb(0xd2d0d1)));
    this->chart()->setPlotAreaBackgroundBrush(QBrush(QRgb(0x4c4547)));
    this->chart()->setPlotAreaBackgroundVisible(true);

    // Zoom over mouse drawn rectangle
    setRubberBand(QChartView::RectangleRubberBand);
  }

  void ChartView::wheelEvent(QWheelEvent* event) 
  {
    // Zoom in/out on mouse wheel scroll
    qreal factor = event->angleDelta().y() > 0 ? 0.5 : 2.0;
    this->chart()->zoom(factor);
    event->accept();
    QChartView::wheelEvent(event);
  }

  void ChartView::keyPressEvent(QKeyEvent *event)
  {
    auto scrollStep = 20;
    switch (event->key())
    {
      case Qt::Key_Left:
	this->chart()->scroll(-scrollStep, 0);
	break;
      case Qt::Key_Right:
	this->chart()->scroll(scrollStep, 0);
	break;
      case Qt::Key_Down:
	this->chart()->scroll(0, -scrollStep);
	break;
      case Qt::Key_Up:
	this->chart()->scroll(0, scrollStep);
	break;
      default:
	QChartView::keyPressEvent(event);
    }
  }

}
