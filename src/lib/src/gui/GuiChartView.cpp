#define GUICHARTVIEW_CPP
#include <gui/GuiChartView.hpp>
#include <gui/GuiState.hpp>
//#include <OSMMap.hpp>

#include <QtCharts/QLineSeries>

namespace attpcfe {

  GuiChartView::GuiChartView(QChart* chart) : QChartView{chart}
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

  void GuiChartView::wheelEvent(QWheelEvent* event) 
  {
    // Zoom in/out on mouse wheel scroll
    qreal factor = event->angleDelta().y() > 0 ? 0.5 : 2.0;
    this->chart()->zoom(factor);
    event->accept();
    QChartView::wheelEvent(event);
  }

  void GuiChartView::keyPressEvent(QKeyEvent *event)
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

  /*
  void GuiChartView::drawMap()
  {
    GuiState& _state = GuiState::instance();
    
    auto bounds = new QLineSeries{};
    //bounds->setUseOpenGL(true);
    bounds->append(_state.map().bounds().minlon(), _state.map().bounds().minlat());
    bounds->append(_state.map().bounds().minlon(), _state.map().bounds().maxlat());
    bounds->append(_state.map().bounds().maxlon(), _state.map().bounds().maxlat());
    bounds->append(_state.map().bounds().maxlon(), _state.map().bounds().minlat());
    bounds->append(_state.map().bounds().minlon(), _state.map().bounds().minlat());
    QPen pen(Qt::black);
    pen.setWidth(1);
    bounds->setPen(pen);
    this->chart()->addSeries(bounds);
    this->chart()->createDefaultAxes();
    QPen axisPen(Qt::black);
    axisPen.setWidth(2);
    this->chart()->axisX()->setLinePen(axisPen);
    this->chart()->axisY()->setLinePen(axisPen);
    QBrush axisBrush(Qt::black);
    this->chart()->axisX()->setLabelsBrush(axisBrush);
    this->chart()->axisY()->setLabelsBrush(axisBrush);
    this->chart()->axisX()->setGridLineVisible(false);
    this->chart()->axisY()->setGridLineVisible(false);

    
    for (auto const& way : _state.map().ways())
    {
      auto nodes = new QLineSeries{};
      //nodes->setUseOpenGL(true);
      nodes->setPen(pen);
      for (auto const& node : way.nodes())
      {
	nodes->append(node.lonlat().first, node.lonlat().second);
      }
      this->chart()->addSeries(nodes);
      this->chart()->setAxisX(this->chart()->axisX(), nodes);
      this->chart()->setAxisY(this->chart()->axisY(), nodes);
    }
  }
  */
}
