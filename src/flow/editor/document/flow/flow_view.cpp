/* ------------------------------------ Qt ---------------------------------- */
#include <QWheelEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_scene.h"
#include "flow/editor/document/flow/flow_view.h"
/* -------------------------------------------------------------------------- */

FlowView::FlowView(QWidget *parent)
    : QGraphicsView(parent), m_background_color(53, 53, 53),
      m_small_grid_color(60, 60, 60), m_grid_color(25, 25, 25)
{
  setDragMode(QGraphicsView::ScrollHandDrag);
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

void FlowView::scaleUp()
{
  double const step = 1.2;
  double const factor = std::pow(step, 1.0);

  QTransform t = transform();
  if (t.m11() > 2.0) return;

  scale(factor, factor);
}

void FlowView::scaleDown()
{
  double const step = 1.2;
  double const factor = std::pow(step, -1.0);

  scale(factor, factor);
}

void FlowView::wheelEvent(QWheelEvent *event)
{
  QPoint delta = event->angleDelta();
  if (delta.y() == 0)
  {
    event->ignore();
    return;
  }

  double const d = static_cast<double>(delta.y()) / std::abs(delta.y());
  if (d > 0.0) scaleUp();
  else
    scaleDown();
}

void FlowView::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Shift:
      setDragMode(QGraphicsView::RubberBandDrag);
      break;

    default:
      break;
  }

  QGraphicsView::keyPressEvent(event);
}

void FlowView::keyReleaseEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Shift:
      setDragMode(QGraphicsView::ScrollHandDrag);
      break;

    default:
      break;
  }
  QGraphicsView::keyReleaseEvent(event);
}

void FlowView::mousePressEvent(QMouseEvent *event)
{
  QGraphicsView::mousePressEvent(event);
  if (event->button() == Qt::LeftButton)
    m_mouse_click_pos = mapToScene(event->pos());
}

void FlowView::mouseMoveEvent(QMouseEvent *event)
{
  QGraphicsView::mouseMoveEvent(event);
  if (
    scene()->mouseGrabberItem() == nullptr &&
    event->buttons() == Qt::LeftButton)
  {
    if ((event->modifiers() & Qt::ShiftModifier) == 0)
    {
      QPointF difference = m_mouse_click_pos - mapToScene(event->pos());
      setSceneRect(sceneRect().translated(difference.x(), difference.y()));
    }
  }
}
