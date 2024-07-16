/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/cubic_path_item.h"

#include "flow_document/component/scene/style/style.h"
#include "flow_document/component/scene/style/style_manager.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
#include <QStyleOptionGraphicsItem>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {

/* -------------------------------- Qtils ------------------------------- */

const ConnectionStyle& getCubicPathStyle() {
  return StyleManager::getInstance().getStyle().getConnectionStyle();
}

}  // namespace

/* ----------------------------- CubicPathItem -------------------------- */

CubicPathItem::CubicPathItem(QGraphicsItem* parent) : QGraphicsItem(parent) {}

CubicPathItem::~CubicPathItem() = default;

void CubicPathItem::setStartPos(QPointF start) {
  prepareGeometryChange();
  const auto end = m_path.pointAtPercent(1);
  const auto [c1, c2] = calculateControlPoints(start, end);

  m_path = QPainterPath(start);
  m_path.cubicTo(c1, c2, end);
}

QPointF CubicPathItem::getStartPos() const { return m_path.pointAtPercent(0); }

void CubicPathItem::setEndPos(QPointF end) {
  prepareGeometryChange();
  const auto start = m_path.pointAtPercent(0);
  const auto [c1, c2] = calculateControlPoints(start, end);

  m_path = QPainterPath(start);
  m_path.cubicTo(c1, c2, end);
}

QPointF CubicPathItem::getEndPos() const { return m_path.pointAtPercent(1); }

QRectF CubicPathItem::boundingRect() const { return m_path.boundingRect(); }

QPainterPath CubicPathItem::shape() const { return m_path; }

void CubicPathItem::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget) {
  const auto& style = getCubicPathStyle();

  auto pen = QPen{};
  pen.setWidth(style.getThickness());
  pen.setColor(style.getColor());

  painter->setClipRect(option->exposedRect);
  painter->setPen(pen);
  painter->setBrush(Qt::NoBrush);
  painter->drawPath(m_path);
}

CubicPathItem::PointsPair CubicPathItem::calculateControlPoints(
    const QPointF& start, const QPointF& end) const {
  const auto default_offset = 200.0;

  auto x_distance = end.x() - start.x();
  auto horizontal_offset = std::min(default_offset, std::abs(x_distance));
  auto vertical_offset = 0;
  auto ratioX = 0.5;

  if (x_distance <= 0) {
    auto y_distance = end.y() - start.y() + 20;
    auto vector = y_distance < 0 ? -1.0 : 1.0;

    vertical_offset = std::min(default_offset, std::abs(y_distance)) * vector;
    ratioX = 1.0;
  }

  horizontal_offset *= ratioX;

  auto c1 = QPointF(start.x() + horizontal_offset, start.y() + vertical_offset);
  auto c2 = QPointF(end.x() - horizontal_offset, end.y() - vertical_offset);

  return std::make_pair(c1, c2);
}

}  // namespace flow_document