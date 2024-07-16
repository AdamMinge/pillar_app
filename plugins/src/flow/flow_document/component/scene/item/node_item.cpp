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
#include <QLineF>
#include <QPainter>
#include <QScopedValueRollback>
#include <QStyleOptionGraphicsItem>
/* --------------------------------- Standard ------------------------------- */
#include <limits>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {

/* -------------------------------- Qtils ------------------------------- */

const NodeStyle &getNodeStyle() {
  return StyleManager::getInstance().getStyle().getNodeStyle();
}

const PinStyle &getPinStyle() {
  return StyleManager::getInstance().getStyle().getPinStyle();
}

[[nodiscard]] QRectF scaleRect(const QRectF &rect, qreal scale) {
  const auto w = rect.width() * scale;
  const auto h = rect.height() * scale;

  const auto x_offset = (rect.width() - w) / 2.0;
  const auto y_offset = (rect.height() - h) / 2.0;

  return QRectF(rect.x() + x_offset, rect.y() + y_offset, w, h);
}

}  // namespace

/* ----------------------------- NodeGeometry --------------------------- */

NodeGeometry::NodeGeometry(const NodeItem &node_item)
    : m_node_item(node_item) {}

NodeGeometry::~NodeGeometry() = default;

void NodeGeometry::recalculate() {
  const auto &node_style = getNodeStyle();

  const auto label_size = calculateLabelSize();
  const auto pins_size = calculatePinsSize();
  const auto widget_size = calculateEmbeddedWidgetSize();

  const auto node_size = QSizeF(
      std::max(pins_size.width() + widget_size.width(), label_size.width()),
      label_size.height() + std::max(pins_size.height(), widget_size.height()));

  m_rect = QRectF(-node_size.width() / 2.0, -node_size.height() / 2.0,
                  node_size.width(), node_size.height());

  m_label_position = calculateLabelPosition(m_rect, label_size);
  m_pin_positions = calculatePinPositions(m_rect, label_size);
  m_embedded_widget_position =
      calculateEmbeddedWidgetPosition(m_rect, widget_size);

  m_rect.adjust(-node_style.getMargins().left(), -node_style.getMargins().top(),
                node_style.getMargins().right(),
                node_style.getMargins().bottom());
}

QRectF NodeGeometry::getBoundingRect() const { return m_rect; }

QPointF NodeGeometry::getLabelPosition() const { return m_label_position; }

QPointF NodeGeometry::getPinPosition(Pin::Type type, int index) const {
  return m_pin_positions.value(std::make_pair(type, index), QPointF{});
}

QPointF NodeGeometry::getPinLabelPosition(Pin::Type type, int index) const {
  const auto &pin_style = getPinStyle();
  const auto font_metrics = QFontMetricsF(pin_style.getFont());
  const auto label = m_node_item.getNode()->getPin(type, index).getCaption();

  auto pin_pos = getPinPosition(type, index);
  pin_pos.ry() += font_metrics.height() / 3.0;

  if (type == Pin::Type::In) {
    pin_pos.rx() +=
        pin_style.getSize().width() / 2.0 + font_metrics.height() / 2.0;
  } else {
    pin_pos.rx() -= pin_style.getSize().width() / 2.0 +
                    font_metrics.horizontalAdvance(label) +
                    font_metrics.height() / 2.0;
  }

  return pin_pos;
}

QPointF NodeGeometry::getEmbeddedWidgetPosition() const {
  return m_embedded_widget_position;
}

NodeGeometry::FoundPin NodeGeometry::findNearestPin(
    const QPointF &search_pos, qreal search_scale,
    std::optional<Pin::Type> type) const {
  const auto &pin_style = getPinStyle();

  auto found_pin = FoundPin{};
  auto nearest_len = std::numeric_limits<qreal>::max();

  for (auto iter = m_pin_positions.begin(); iter != m_pin_positions.end();
       ++iter) {
    const auto &pin_type = iter.key().first;
    const auto &pin_index = iter.key().second;

    if (type.has_value() && pin_type != type.value()) continue;

    const auto &pos = iter.value();
    const auto &size = pin_style.getSize();
    const auto len = QLineF(search_pos, pos).length();

    auto rect =
        QRectF(pos - QPointF(size.width() / 2, size.height() / 2), size / 2);
    rect = scaleRect(rect, search_scale);

    if (!rect.contains(search_pos) || len >= nearest_len) continue;

    found_pin = std::make_pair(pin_index, pin_type);
    nearest_len = len;
  }

  return found_pin;
}

QSizeF NodeGeometry::calculateLabelSize() const {
  const auto &node_style = getNodeStyle();
  const auto font_metrics = QFontMetricsF(node_style.getFont());
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
      QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return label_size;
}

QSizeF NodeGeometry::calculateEmbeddedWidgetSize() const {
  const auto &node_style = getNodeStyle();
  const auto &pin_style = getPinStyle();
  const auto font_metrics = QFontMetricsF(node_style.getFont());
  const auto widget = m_node_item.getEmbeddedWidget();

  auto size = QSizeF(font_metrics.height() * 2, 0);
  if (widget) {
    const auto widget_size = widget->size().toSizeF();
    const auto margins = pin_style.getMargins();

    size = QSizeF(std::max(size.width(), widget_size.width()),
                  std::max(size.height(), widget_size.height()));
  }

  return size;
}

QSizeF NodeGeometry::calculatePinsSize() const {
  const auto &pin_style = getPinStyle();
  const auto font_metrics = QFontMetricsF(pin_style.getFont());

  auto max_pins =
      std::max(m_node_item.getNode()->getPinsCounts(Pin::Type::In),
               m_node_item.getNode()->getPinsCounts(Pin::Type::Out));

  auto width =
      calculatePinsWidth(Pin::Type::In) + calculatePinsWidth(Pin::Type::Out);
  auto height =
      std::max(pin_style.getMargins().top() + pin_style.getSize().height() +
                   pin_style.getMargins().bottom(),
               pin_style.getMargins().top() + font_metrics.height() +
                   pin_style.getMargins().bottom()) *
      max_pins;

  return {width, height};
}

qreal NodeGeometry::calculatePinsWidth(Pin::Type type) const {
  const auto &pin_style = getPinStyle();
  const auto font_metrics = QFontMetricsF(pin_style.getFont());

  auto width = pin_style.getMargins().left() + pin_style.getSize().width() * 2 +
               pin_style.getMargins().right();

  for (auto i = 0; i < m_node_item.getNode()->getPinsCounts(type); ++i) {
    const auto name = m_node_item.getNode()->getPin(type, i).getCaption();
    const auto new_width =
        pin_style.getMargins().left() + pin_style.getSize().width() * 2 +
        pin_style.getMargins().right() + font_metrics.horizontalAdvance(name);

    width = std::max(width, new_width);
  }

  return width;
}

QPointF NodeGeometry::calculateLabelPosition(const QRectF &rect,
                                             const QSizeF &label) const {
  return QPointF{rect.center().x() - label.width() / 2,
                 rect.top() + label.height() / 2};
}

NodeGeometry::PinToPos NodeGeometry::calculatePinPositions(
    const QRectF &rect, const QSizeF &label) const {
  const auto &pin_style = getPinStyle();
  const auto node = m_node_item.getNode();

  auto pin_positions = PinToPos{};
  for (auto type : {Pin::Type::In, Pin::Type::Out}) {
    auto pins_count = node->getPinsCounts(type);
    auto height_step = (rect.height() - label.height()) / (pins_count + 1);

    for (auto index = 0; index < node->getPinsCounts(type); ++index) {
      const auto x = type == Pin::Type::In
                         ? rect.left() + pin_style.getMargins().left()
                         : rect.right() - pin_style.getMargins().right();
      const auto y = rect.top() + label.height() + (height_step * (index + 1));

      pin_positions.insert(std::make_pair(type, index), QPointF(x, y));
    }
  }

  return pin_positions;
}

QPointF NodeGeometry::calculateEmbeddedWidgetPosition(
    const QRectF &rect, const QSizeF &size) const {
  const auto center = rect.center();
  return QPointF(center.x() - size.width() / 2, center.y());
}

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
  const auto &node_style = getNodeStyle();
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
  const auto &node_style = getNodeStyle();
  const auto node = m_node_item.getNode();
  const auto &geometry = m_node_item.getGeometry();

  const auto label = node->getName();
  const auto label_pos = geometry.getLabelPosition();

  painter->save();
  painter->setFont(node_style.getFont());
  painter->setPen(node_style.getFontColor());
  painter->drawText(label_pos, label);
  painter->restore();
}

void NodePainter::paintNodePins(QPainter *painter,
                                const QStyleOptionGraphicsItem *option) {
  const auto &pin_style = getPinStyle();
  const auto node = m_node_item.getNode();
  const auto &geometry = m_node_item.getGeometry();

  for (auto type : {Pin::Type::In, Pin::Type::Out}) {
    for (auto index = 0; index < node->getPinsCounts(type); ++index) {
      const auto pin_pos = geometry.getPinPosition(type, index);

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
  const auto &pin_style = getPinStyle();
  const auto node = m_node_item.getNode();
  const auto &geometry = m_node_item.getGeometry();

  for (auto type : {Pin::Type::In, Pin::Type::Out}) {
    for (auto index = 0; index < node->getPinsCounts(type); ++index) {
      const auto pin_label_pos = geometry.getPinLabelPosition(type, index);
      const auto pin_label = node->getPin(type, index).getCaption();

      painter->save();
      painter->setFont(pin_style.getFont());
      painter->setPen(pin_style.getFontColor());
      painter->drawText(pin_label_pos, pin_label);
      painter->restore();
    }
  }
}

/* ------------------------------- NodeItem ----------------------------- */

NodeItem::NodeItem(Node *node, FlowDocument *document, QGraphicsItem *parent)
    : ObjectItem(node, document, parent),
      m_selection_item(new NodeSelectionItem(node, document, this)),
      m_node_painter(*this),
      m_node_geometry(*this),
      m_proxy_widget(nullptr) {}

NodeItem::~NodeItem() {
  if (m_proxy_widget) {
    m_proxy_widget->setWidget(nullptr);
  }
}

void NodeItem::init() {
  setPos(getNode()->getPosition());
  setVisible(getNode()->isVisible());
  setAcceptHoverEvents(true);

  embedWidget();
  onSceneChanged();
}

Node *NodeItem::getNode() const { return static_cast<Node *>(getObject()); }

const NodePainter &NodeItem::getPainter() const { return m_node_painter; }

const NodeGeometry &NodeItem::getGeometry() const { return m_node_geometry; }

QRectF NodeItem::boundingRect() const {
  return m_node_geometry.getBoundingRect();
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  painter->setClipRect(option->exposedRect);
  m_node_painter.paint(painter, option);
}

QWidget *NodeItem::getEmbeddedWidget() const { return nullptr; }

void NodeItem::onSceneChanged() { updateGeometry(); }

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
  if (properties & Name) {
    updateGeometry();
  }
}

void NodeItem::embedWidget() {
  if (auto widget = getEmbeddedWidget()) {
    m_proxy_widget = new QGraphicsProxyWidget(this);
    m_proxy_widget->setWidget(widget);
    m_proxy_widget->setOpacity(1.0);
    m_proxy_widget->setFlag(QGraphicsItem::ItemIgnoresParentOpacity);
  }
}

void NodeItem::updateGeometry() {
  prepareGeometryChange();
  m_node_geometry.recalculate();

  if (m_proxy_widget) {
    m_proxy_widget->setPos(m_node_geometry.getEmbeddedWidgetPosition());
  }

  update();
}

}  // namespace flow_document