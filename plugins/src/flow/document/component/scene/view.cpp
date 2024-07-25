/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/view.h"

#include "flow/document/component/scene/scene.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScrollBar>
#include <QWheelEvent>
/* -------------------------------------------------------------------------- */

namespace flow {

FlowView::FlowView(QWidget *parent)
    : QGraphicsView(parent),
      m_background_color(53, 53, 53),
      m_small_grid_color(60, 60, 60),
      m_grid_color(25, 25, 25) {
  setRenderHint(QPainter::Antialiasing);
  setMouseTracking(true);

  setBackgroundBrush(m_background_color);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  setCacheMode(QGraphicsView::CacheBackground);
  setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

  setScaleRange(0.3, 2);
}

FlowView::~FlowView() = default;

void FlowView::setScene(FlowScene *scene) { QGraphicsView::setScene(scene); }

FlowScene *FlowView::getScene() const {
  auto flow_scene = dynamic_cast<FlowScene *>(scene());
  Q_ASSERT(flow_scene || !scene());

  return flow_scene;
}

void FlowView::setScaleRange(double minimum, double maximum) {
  if (maximum < minimum) std::swap(minimum, maximum);
  minimum = std::max(0.0, minimum);
  maximum = std::max(0.0, maximum);

  m_scale_range = {minimum, maximum};
  setupScale(transform().m11());
}

FlowView::ScaleRange FlowView::getScaleRange() const { return m_scale_range; }

void FlowView::drawBackground(QPainter *painter, const QRectF &rect) {
  QGraphicsView::drawBackground(painter, rect);

  auto drawGrid = [&painter, this](auto grid_step) {
    auto window_rect = this->rect();
    auto tl = mapToScene(window_rect.topLeft());
    auto br = mapToScene(window_rect.bottomRight());

    auto left = std::floor(tl.x() / grid_step - 0.5);
    auto right = std::floor(br.x() / grid_step + 1.0);
    auto bottom = std::floor(tl.y() / grid_step - 0.5);
    auto top = std::floor(br.y() / grid_step + 1.0);

    for (auto xi = static_cast<int>(left); xi <= static_cast<int>(right);
         ++xi) {
      QLineF line(xi * grid_step, bottom * grid_step, xi * grid_step,
                  top * grid_step);

      painter->drawLine(line);
    }

    for (auto yi = static_cast<int>(bottom); yi <= static_cast<int>(top);
         ++yi) {
      QLineF line(left * grid_step, yi * grid_step, right * grid_step,
                  yi * grid_step);
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

void FlowView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  if (event->button() == Qt::RightButton) {
    m_mouse_clicked_pos = mapToScene(event->pos());
  }
}

void FlowView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);

  if (event->buttons() == Qt::RightButton) {
    auto diff = m_mouse_clicked_pos - mapToScene(event->pos());
    diff *= transform().m11();

    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + diff.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() + diff.y());
  }
}

void FlowView::scaleUp() {
  const auto step = 1.2;
  const auto factor = std::pow(step, 1.0);

  if (m_scale_range.maximum > 0) {
    auto t = transform();
    t.scale(factor, factor);
    if (t.m11() >= m_scale_range.maximum) {
      setupScale(t.m11());
      return;
    }
  }

  scale(factor, factor);
}

void FlowView::scaleDown() {
  const auto step = 1.2;
  const auto factor = std::pow(step, -1.0);

  if (m_scale_range.minimum > 0) {
    auto t = transform();
    t.scale(factor, factor);
    if (t.m11() <= m_scale_range.minimum) {
      setupScale(t.m11());
      return;
    }
  }

  scale(factor, factor);
}

void FlowView::setupScale(double scale) {
  scale =
      std::max(m_scale_range.minimum, std::min(m_scale_range.maximum, scale));

  if (scale <= 0) return;
  if (scale == transform().m11()) return;

  QTransform matrix;
  matrix.scale(scale, scale);
  setTransform(matrix, false);
}

void FlowView::wheelEvent(QWheelEvent *event) {
  QPoint delta = event->angleDelta();
  if (delta.y() == 0) {
    event->ignore();
    return;
  }

  double const d = static_cast<double>(delta.y()) / std::abs(delta.y());
  if (d > 0.0)
    scaleUp();
  else
    scaleDown();
}

void FlowView::showEvent(QShowEvent *event) {
  QGraphicsView::showEvent(event);
  QGraphicsView::centerOn(sceneRect().center());
}

void FlowView::enterEvent(QEnterEvent *event) {
  QGraphicsView::enterEvent(event);
  if (!hasFocus()) setFocus();
}

}  // namespace flow