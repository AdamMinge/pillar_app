/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_view.h"
#include "flow/editor/document/flow/flow_scene.h"
/* -------------------------------------------------------------------------- */

FlowView::FlowView(QWidget *parent)
    : QGraphicsView(parent), m_background_color(53, 53, 53),
      m_small_grid_color(60, 60, 60), m_grid_color(25, 25, 25)
{
  setRenderHint(QPainter::Antialiasing);
  setBackgroundBrush(m_background_color);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  setCacheMode(QGraphicsView::CacheBackground);
  setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

FlowView::~FlowView() = default;

void FlowView::setScene(FlowScene *scene) { QGraphicsView::setScene(scene); }

FlowScene *FlowView::getScene() const
{
  auto flow_scene = dynamic_cast<FlowScene *>(scene());
  Q_ASSERT(flow_scene || !scene());

  return flow_scene;
}

void FlowView::drawBackground(QPainter *painter, const QRectF &rect)
{
  QGraphicsView::drawBackground(painter, rect);

  auto drawGrid = [&painter, this](auto grid_step) {
    QRect window_rect = this->rect();
    QPointF tl = mapToScene(window_rect.topLeft());
    QPointF br = mapToScene(window_rect.bottomRight());

    auto left = std::floor(tl.x() / grid_step - 0.5);
    auto right = std::floor(br.x() / grid_step + 1.0);
    auto bottom = std::floor(tl.y() / grid_step - 0.5);
    auto top = std::floor(br.y() / grid_step + 1.0);

    for (auto xi = static_cast<int>(left); xi <= static_cast<int>(right); ++xi)
    {
      QLineF line(
        xi * grid_step, bottom * grid_step, xi * grid_step, top * grid_step);

      painter->drawLine(line);
    }

    for (auto yi = static_cast<int>(bottom); yi <= static_cast<int>(top); ++yi)
    {
      QLineF line(
        left * grid_step, yi * grid_step, right * grid_step, yi * grid_step);
      painter->drawLine(line);
    }
  };

  const auto small_grid_pen = QPen(m_small_grid_color, 1.0);
  painter->setPen(small_grid_pen);
  drawGrid(15);

  const auto grid_pen = QPen(m_grid_color, 1.0);
  painter->setPen(grid_pen);
  drawGrid(150);
}
