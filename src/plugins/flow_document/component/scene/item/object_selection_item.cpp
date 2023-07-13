/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_selection_item.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/dpi/dpi.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- ObjectOutlineItem -------------------------- */

ObjectOutlineItem::ObjectOutlineItem(Role role, QGraphicsItem *parent)
    : QGraphicsItem(parent) {
  switch (role) {
    case Role::Hover:
      setOpacity(0.6);
      break;
  }
}

ObjectOutlineItem::~ObjectOutlineItem() = default;

QPainterPath ObjectOutlineItem::shape() const { return QPainterPath(); }

QRectF ObjectOutlineItem::boundingRect() const {
  auto rect = QRectF{};
  if (auto parent = parentItem(); parent) {
    rect = mapFromParent(parent->boundingRect()).boundingRect();
  }

  return rect;
}

void ObjectOutlineItem::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget) {
  const auto bounding_rect = boundingRect();
  if (bounding_rect.isEmpty()) return;

  const auto lines = std::array<QLineF, 4>{
      QLineF(bounding_rect.topLeft(), bounding_rect.topRight()),
      QLineF(bounding_rect.bottomLeft(), bounding_rect.bottomRight()),
      QLineF(bounding_rect.topLeft(), bounding_rect.bottomLeft()),
      QLineF(bounding_rect.topRight(), bounding_rect.bottomRight())};

  const auto device_pixel_ratio = painter->device()->devicePixelRatioF();
  const auto dash_length = std::ceil(utils::dpiScaled(2) * device_pixel_ratio);

  QPen pen(Qt::white, 1.5 * device_pixel_ratio, Qt::SolidLine);
  pen.setCosmetic(true);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(pen);
  painter->drawLines(lines.data(), 4);

  pen.setColor(Qt::black);
  pen.setCapStyle(Qt::FlatCap);
  pen.setDashPattern({dash_length, dash_length});
  painter->setPen(pen);
  painter->drawLines(lines.data(), 4);
}

/* ---------------------------- ObjectSelectionItem ------------------------- */

ObjectSelectionItem::ObjectSelectionItem(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_hover(new ObjectOutlineItem(ObjectOutlineItem::Role::Hover, this)),
      m_selection(
          new ObjectOutlineItem(ObjectOutlineItem::Role::Selection, this)) {
  setFlag(QGraphicsItem::ItemHasNoContents);
}

ObjectSelectionItem::~ObjectSelectionItem() = default;

QPainterPath ObjectSelectionItem::shape() const { return QPainterPath(); }

QRectF ObjectSelectionItem::boundingRect() const {
  auto rect = QRectF{};
  if (auto parent = parentItem(); parent) {
    rect = mapFromParent(parent->boundingRect()).boundingRect();
  }

  return rect;
}

void ObjectSelectionItem::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget) {}

}  // namespace flow_document