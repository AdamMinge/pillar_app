/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_selection_item.h"

#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/dpi/dpi.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- ObjectOutlineItem -------------------------- */

ObjectOutlineItem::ObjectOutlineItem(Role role, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_dash_offset(0) {
  switch (role) {
    case Role::Hover:
      setOpacity(0.6);
      break;
    case Role::Selection:
      m_timer.start(100);
      m_timer.callOnTimeout([this]() {
        m_dash_offset += 1;
        update();
      });
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
  pen.setDashOffset(m_dash_offset);
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
  setHovered(false);
  setSelected(false);
}

ObjectSelectionItem::~ObjectSelectionItem() = default;

void ObjectSelectionItem::setHovered(bool hovered) {
  m_hover->setVisible(hovered);
}

void ObjectSelectionItem::setSelected(bool selected) {
  m_selection->setVisible(selected);
}

bool ObjectSelectionItem::isHovered() const { return m_hover->isVisible(); }

bool ObjectSelectionItem::isSelected() const {
  return m_selection->isVisible();
}

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

/* ----------------------------- NodeSelectionItem -------------------------- */

NodeSelectionItem::NodeSelectionItem(Node *node, FlowDocument *document,
                                     QGraphicsItem *parent)
    : ObjectSelectionItem(parent), m_node(node), m_document(document) {
  connect(m_document, &FlowDocument::selectedNodesChanged, this,
          [this](const auto &nodes) { setSelected(nodes.contains(m_node)); });
  connect(m_document, &FlowDocument::hoveredNodesChanged, this,
          [this](const auto &nodes) { setHovered(nodes.contains(m_node)); });
}

NodeSelectionItem::~NodeSelectionItem() = default;

}  // namespace flow_document