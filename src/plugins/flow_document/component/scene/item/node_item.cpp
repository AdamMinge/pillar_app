/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/node_item.h"

#include "flow_document/command/change_node.h"
#include "flow_document/component/scene/item/object_selection_item.h"
#include "flow_document/component/scene/style/style.h"
#include "flow_document/component/scene/style/style_manager.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
#include <QScopedValueRollback>
#include <QStyleOptionGraphicsItem>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {

/* -------------------------------- Utils ------------------------------- */

const NodeStyle &getNodeStyle(const NodeItem &item) {
  return StyleManager::getInstance().getStyle().getNodeStyle();
}

const PinStyle &getPinStyle(const NodeItem &item) {
  return StyleManager::getInstance().getStyle().getPinStyle();
}

}  // namespace

/* ------------------------------- NodeItem ----------------------------- */

NodeItem::NodeItem(Node *node, FlowDocument *document, QGraphicsItem *parent)
    : ObjectItem(node, document, parent),
      m_selection_item(new NodeSelectionItem(node, document, this)),
      m_node_painter(std::make_unique<NodePainter>(*this)),
      m_node_geometry(std::make_unique<NodeGeometry>(*this)) {}

NodeItem::~NodeItem() = default;

Node *NodeItem::getNode() const { return static_cast<Node *>(getObject()); }

const NodePainter *NodeItem::getPainter() const { return m_node_painter.get(); }

const NodeGeometry *NodeItem::getGeometry() const {
  return m_node_geometry.get();
}

QRectF NodeItem::boundingRect() const {
  return m_node_geometry->getBoundingRect();
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  painter->setClipRect(option->exposedRect);
  m_node_painter->paint(painter, option);
}

void NodeItem::onEvent(const ChangeEvent &event) {
  if (event.getType() == NodesChangeEvent::type) {
    const auto &node_event = static_cast<const NodesChangeEvent &>(event);
    if (node_event.contains(getNode())) onUpdate(node_event);
  }
}

void NodeItem::onUpdate(const NodesChangeEvent &event) {
  const auto node = getNode();
  const auto properties = event.getProperties();

  using enum NodesChangeEvent::Property;
  if (properties & Visible) {
    setVisible(node->isVisible());
  }
  if (properties & Position) {
    setPos(node->getPosition());
  }
}

/* ----------------------------- NodeGeometry --------------------------- */

NodeGeometry::NodeGeometry(const NodeItem &node_item) : m_node_item(node_item) {
  recalculate();
}

NodeGeometry::~NodeGeometry() = default;

void NodeGeometry::recalculate() {
  const auto node_style = getNodeStyle(m_node_item);
  const auto label_size = calculateLabelSize();
  const auto pins_size = calculatePinsSize();
  const auto widget_size = calculateWidgetSize();

  m_size.setWidth(
      std::max(pins_size.width() + widget_size.width(), label_size.width()) +
      node_style.getMargins().left() + node_style.getMargins().right());
  m_size.setHeight(
      label_size.height() + std::max(pins_size.height(), widget_size.height()) +
      node_style.getMargins().top() + node_style.getMargins().bottom());

  m_label_position = calculateLabelPosition();
  m_pin_positions = calculatePinPositions();
  m_widget_position = calculateWidgetPosition();
}

QRectF NodeGeometry::getBoundingRect() const {
  return QRectF{QPointF(-m_size.width() / 2.0, -m_size.height() / 2.0), m_size};
}

QPointF NodeGeometry::getLabelPosition() const { return m_label_position; }

QPointF NodeGeometry::getPinPosition(Pin::Type type, int index) const {
  return m_pin_positions.value(std::make_pair(type, index), QPointF{});
}

QPointF NodeGeometry::getPinLabelPosition(Pin::Type type, int index) const {
  const auto pin_style = getPinStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(pin_style.getFont());
  const auto label = m_node_item.getNode()->getPin(type, index).getCaption();

  auto pin_pos = getPinPosition(type, index);
  pin_pos.ry() -= pin_style.getSize().height() + font_metrics.height() / 3.0;
  pin_pos.rx() -= font_metrics.horizontalAdvance(label) / 2.0;

  return pin_pos;
}

QPointF NodeGeometry::getWidgetPosition() const { return m_widget_position; }

QSizeF NodeGeometry::calculateLabelSize() const {
  const auto node_style = getNodeStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(node_style.getFont());
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
      QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return label_size;
}

QSizeF NodeGeometry::calculateWidgetSize() const { return QSizeF{}; }

QSizeF NodeGeometry::calculatePinsSize() const {
  const auto pin_style = getPinStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(pin_style.getFont());

  auto max_pins =
      std::max(m_node_item.getNode()->getPinsCounts(Pin::Type::In),
               m_node_item.getNode()->getPinsCounts(Pin::Type::Out));

  auto width =
      calculatePinsWidth(Pin::Type::In) + calculatePinsWidth(Pin::Type::Out);
  auto height = (pin_style.getSize().height() + pin_style.getMargins().top() +
                 pin_style.getMargins().left() + font_metrics.height()) *
                max_pins;

  return {width, height};
}

float NodeGeometry::calculatePinsWidth(Pin::Type type) const {
  const auto pin_style = getPinStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(pin_style.getFont());

  auto width = pin_style.getMargins().left() + pin_style.getMargins().right();
  for (auto i = 0; i < m_node_item.getNode()->getPinsCounts(type); ++i) {
    const auto name = m_node_item.getNode()->getPin(type, i).getCaption();
    width = std::max(width, font_metrics.horizontalAdvance(name));
  }

  return static_cast<float>(width);
}

QPointF NodeGeometry::calculateLabelPosition() const {
  const auto node_style = getNodeStyle(m_node_item);
  const auto rect = getBoundingRect();
  const auto font_metrics = QFontMetricsF(node_style.getFont());
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
      QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return QPointF{
      rect.center().x() - label_size.width() / 2,
      rect.top() + label_size.height() / 2 + node_style.getMargins().top()};
}

NodeGeometry::PinToPos NodeGeometry::calculatePinPositions() const {
  const auto node_style = getNodeStyle(m_node_item);
  const auto pin_style = getPinStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto rect = getBoundingRect();
  const auto label_size = calculateLabelSize();
  const auto label_pos = calculateLabelPosition();

  auto pin_positions = PinToPos{};
  for (auto type : {Pin::Type::In, Pin::Type::Out}) {
    auto pins_count = node->getPinsCounts(type);
    auto height_step = (rect.height() -
                        (label_size.height() + node_style.getMargins().top())) /
                       (pins_count + 1);

    for (auto index = 0; index < node->getPinsCounts(type); ++index) {
      const auto x = type == Pin::Type::In
                         ? rect.left() + pin_style.getMargins().left()
                         : rect.right() - pin_style.getMargins().right();
      const auto y =
          label_pos.y() + label_size.height() / 2 + (height_step * (index + 1));

      pin_positions.insert(std::make_pair(type, index), QPointF(x, y));
    }
  }

  return pin_positions;
}

QPointF NodeGeometry::calculateWidgetPosition() const { return QPointF{}; }

/* ------------------------------ NodePainter --------------------------- */

NodePainter::NodePainter(const NodeItem &node_item) : m_node_item(node_item) {}

NodePainter::~NodePainter() = default;

void NodePainter::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option) {
  paintNodeRect(painter, option);
  paintNodeLabel(painter, option);
  paintNodePins(painter, option);
  paintNodePinLabels(painter, option);
}

void NodePainter::paintNodeRect(QPainter *painter,
                                const QStyleOptionGraphicsItem *option) {
  const auto node_style = getNodeStyle(m_node_item);
  const auto rect = m_node_item.boundingRect();

  QLinearGradient linear_gradient(rect.bottomLeft(), rect.topRight());
  linear_gradient.setColorAt(node_style.getGradientScale()[0],
                             node_style.getGradient()[0]);
  linear_gradient.setColorAt(node_style.getGradientScale()[0],
                             node_style.getGradient()[1]);
  linear_gradient.setColorAt(node_style.getGradientScale()[0],
                             node_style.getGradient()[2]);
  linear_gradient.setColorAt(node_style.getGradientScale()[0],
                             node_style.getGradient()[3]);

  painter->save();
  painter->setBrush(linear_gradient);
  painter->setPen(
      QPen(node_style.getBorderColor(), node_style.getBorderSize()));
  painter->drawRoundedRect(rect, node_style.getBorderRadius(),
                           node_style.getBorderRadius());
  painter->restore();
}

void NodePainter::paintNodeLabel(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option) {
  const auto node_style = getNodeStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();

  const auto label = node->getName();
  const auto label_pos = geometry->getLabelPosition();

  painter->save();
  painter->setFont(node_style.getFont());
  painter->setPen(node_style.getFontColor());
  painter->drawText(label_pos, label);
  painter->restore();
}

void NodePainter::paintNodePins(QPainter *painter,
                                const QStyleOptionGraphicsItem *option) {
  const auto pin_style = getPinStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();

  for (auto type : {Pin::Type::In, Pin::Type::Out}) {
    for (auto index = 0; index < node->getPinsCounts(type); ++index) {
      const auto pin_pos = geometry->getPinPosition(type, index);

      painter->save();
      painter->setBrush(pin_style.getColor());
      painter->setPen(pin_style.getBorderColor());
      painter->drawEllipse(pin_pos, pin_style.getSize().width(),
                           pin_style.getSize().height());
      painter->restore();
    }
  }
}

void NodePainter::paintNodePinLabels(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option) {
  const auto pin_style = getPinStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();

  for (auto type : {Pin::Type::In, Pin::Type::Out}) {
    for (auto index = 0; index < node->getPinsCounts(type); ++index) {
      const auto pin_label_pos = geometry->getPinLabelPosition(type, index);
      const auto pin_label = node->getPin(type, index).getCaption();

      painter->save();
      painter->setFont(pin_style.getFont());
      painter->setPen(pin_style.getFontColor());
      painter->drawText(pin_label_pos, pin_label);
      painter->restore();
    }
  }
}

}  // namespace flow_document