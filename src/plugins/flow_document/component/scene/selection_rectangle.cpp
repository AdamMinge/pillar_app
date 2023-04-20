/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/selection_rectangle.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QPainter>
#include <QPalette>
#include <QPen>
/* -------------------------------------------------------------------------- */

namespace flow_document {

SelectionRectangle::SelectionRectangle(QGraphicsItem *parent)
    : QGraphicsItem(parent) {
  setZValue(10000);
}

SelectionRectangle::~SelectionRectangle() = default;

void SelectionRectangle::setRect(const QRectF &rect) {
  prepareGeometryChange();
  m_rect = rect;
}

QRectF SelectionRectangle::boundingRect() const { return m_rect; }

void SelectionRectangle::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget) {
  if (m_rect.isNull()) return;

  auto highlight_color = QApplication::palette().highlight().color();
  auto black_color = QColor(Qt::black);

  highlight_color.setAlpha(32);
  black_color.setAlpha(128);

  auto highlight_pen = QPen(black_color, 1, Qt::DotLine);
  auto black_pen = QPen(black_color, 1, Qt::DotLine);
  black_pen.setCosmetic(true);

  painter->save();

  painter->setPen(black_pen);
  painter->drawRect(m_rect);

  painter->setPen(highlight_pen);
  painter->setBrush(highlight_color);
  painter->drawRect(m_rect);

  painter->restore();
}

}  // namespace flow_document