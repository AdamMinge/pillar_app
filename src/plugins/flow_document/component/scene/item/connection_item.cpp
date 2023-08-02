/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/connection_item.h"

#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/item/node_item.h"
#include "flow_document/component/scene/style/style.h"
#include "flow_document/component/scene/style/style_manager.h"
#include "flow_document/event/connection_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {

/* -------------------------------- Utils ------------------------------- */

const ConnectionStyle& getConnectionStyle() {
  return StyleManager::getInstance().getStyle().getConnectionStyle();
}

}  // namespace

/* -------------------------- ConnectionGeometry ------------------------ */

ConnectionGeometry::ConnectionGeometry(const ConnectionItem& connection_item)
    : m_connection_item(connection_item) {}

ConnectionGeometry::~ConnectionGeometry() = default;

QRectF ConnectionGeometry::getBoundingRect() const {
  const auto& [out, in] = getConnectionPoints();
  const auto& [c1, c2] = getControlPoints();

  auto basic_rect = QRectF(out, in).normalized();
  auto c1c2_rect = QRectF(c1, c2).normalized();

  auto rect = basic_rect.united(c1c2_rect);

  return rect;
}

QPainterPath ConnectionGeometry::getCubicPath() const {
  const auto& [out, in] = getConnectionPoints();
  const auto& [c1, c2] = getControlPoints();

  auto cubic_path = QPainterPath(out);
  cubic_path.cubicTo(c1, c2, in);
  return cubic_path;
}

const ConnectionGeometry::PointsPair& ConnectionGeometry::getConnectionPoints()
    const {
  return m_connection_points;
}

const ConnectionGeometry::PointsPair& ConnectionGeometry::getControlPoints()
    const {
  return m_control_points;
}

void ConnectionGeometry::recalculate() {
  m_connection_points = calculateConnectionPoints();
  m_control_points = calculateControlPoints();
}

ConnectionGeometry::PointsPair ConnectionGeometry::calculateConnectionPoints()
    const {
  auto out_pin = m_connection_item.getConnection()->getOutputSide().getPinId();
  auto in_pin = m_connection_item.getConnection()->getInputSide().getPinId();
  auto out_node_item = m_connection_item.getOutNodeItem();
  auto in_node_item = m_connection_item.getInNodeItem();
  if (!out_node_item || !in_node_item) return {};

  auto start_position =
      out_node_item->getGeometry().getPinPosition(Pin::Type::Out, out_pin);
  start_position += out_node_item->getNode()->getPosition();

  auto end_position =
      in_node_item->getGeometry().getPinPosition(Pin::Type::In, in_pin);
  end_position += in_node_item->getNode()->getPosition();

  return std::make_pair(start_position, end_position);
}

ConnectionGeometry::PointsPair ConnectionGeometry::calculateControlPoints()
    const {
  const auto& [out, in] = getConnectionPoints();
  const auto default_offset = 200.0;

  auto x_distance = in.x() - out.x();
  auto horizontal_offset = std::min(default_offset, std::abs(x_distance));
  auto vertical_offset = 0;
  auto ratioX = 0.5;

  if (x_distance <= 0) {
    auto y_distance = in.y() - out.y() + 20;
    auto vector = y_distance < 0 ? -1.0 : 1.0;

    vertical_offset = std::min(default_offset, std::abs(y_distance)) * vector;
    ratioX = 1.0;
  }

  horizontal_offset *= ratioX;

  auto c1 = QPointF(out.x() + horizontal_offset, out.y() + vertical_offset);
  auto c2 = QPointF(in.x() - horizontal_offset, in.y() - vertical_offset);

  return std::make_pair(c1, c2);
}

/* --------------------------- ConnectionPainter ------------------------ */

ConnectionPainter::ConnectionPainter(const ConnectionItem& connection_item)
    : m_connection_item(connection_item) {}

ConnectionPainter::~ConnectionPainter() = default;

void ConnectionPainter::paint(QPainter* painter,
                              const QStyleOptionGraphicsItem* option) {
  const auto& style = getConnectionStyle();
  const auto cubic_path = m_connection_item.getGeometry().getCubicPath();

  auto pen = QPen{};
  pen.setWidth(style.getThickness());
  pen.setColor(style.getColor());

  painter->setPen(pen);
  painter->setBrush(Qt::NoBrush);
  painter->drawPath(cubic_path);
}

/* ----------------------------- ConnectionItem ------------------------- */

ConnectionItem::ConnectionItem(Connection* connection, FlowDocument* document,
                               QGraphicsItem* parent)
    : ObjectItem(connection, document, parent),
      m_connection_painter(*this),
      m_connection_geometry(*this),
      m_out_node_item(nullptr),
      m_in_node_item(nullptr) {
  onSceneChanged();
}

ConnectionItem::~ConnectionItem() = default;

Connection* ConnectionItem::getConnection() const {
  return static_cast<Connection*>(getObject());
}

NodeItem* ConnectionItem::getOutNodeItem() const { return m_out_node_item; }

NodeItem* ConnectionItem::getInNodeItem() const { return m_in_node_item; }

const ConnectionPainter& ConnectionItem::getPainter() const {
  return m_connection_painter;
}

const ConnectionGeometry& ConnectionItem::getGeometry() const {
  return m_connection_geometry;
}

QRectF ConnectionItem::boundingRect() const {
  return m_connection_geometry.getBoundingRect();
}

QPainterPath ConnectionItem::shape() const {
  return m_connection_geometry.getCubicPath();
}

void ConnectionItem::paint(QPainter* painter,
                           const QStyleOptionGraphicsItem* option,
                           QWidget* widget) {
  painter->setClipRect(option->exposedRect);
  m_connection_painter.paint(painter, option);
}

void ConnectionItem::onSceneChanged() {
  updateConnection();
  updateGeometry();
}

void ConnectionItem::onEvent(const ChangeEvent& event) {
  if (event.getType() == ConnectionsChangeEvent::type) {
    const auto& connection_event =
        static_cast<const ConnectionsChangeEvent&>(event);
    if (connection_event.contains(getConnection())) onUpdate(connection_event);
  } else if (event.getType() == NodesChangeEvent::type) {
    const auto& node_event = static_cast<const NodesChangeEvent&>(event);

    auto out_node = m_out_node_item ? m_out_node_item->getNode() : nullptr;
    auto in_node = m_in_node_item ? m_in_node_item->getNode() : nullptr;

    if (node_event.contains(out_node) || node_event.contains(in_node)) {
      onUpdate(node_event);
    }
  }
}

void ConnectionItem::onUpdate(const ConnectionsChangeEvent& event) {
  const auto properties = event.getProperties();
  using enum ConnectionsChangeEvent::Property;
  if (properties & Visible) updateVisibility();
}

void ConnectionItem::onUpdate(const NodesChangeEvent& event) {
  const auto properties = event.getProperties();
  using enum NodesChangeEvent::Property;
  if (properties & Visible) updateVisibility();
}

void ConnectionItem::updateConnection() {
  auto flow_scene = static_cast<FlowScene*>(scene());
  if (!flow_scene) return;

  auto connection = getConnection();

  const auto output = connection->getOutputSide();
  const auto input = connection->getInputSide();

  auto out_node_item =
      static_cast<NodeItem*>(flow_scene->findItem(output.getNodeId()));
  auto in_node_item =
      static_cast<NodeItem*>(flow_scene->findItem(input.getNodeId()));

  if (m_out_node_item && m_in_node_item) {
    disconnect(m_out_node_item, &NodeItem::xChanged, this,
               &ConnectionItem::updateGeometry);
    disconnect(m_out_node_item, &NodeItem::yChanged, this,
               &ConnectionItem::updateGeometry);

    disconnect(m_in_node_item, &NodeItem::xChanged, this,
               &ConnectionItem::updateGeometry);
    disconnect(m_in_node_item, &NodeItem::yChanged, this,
               &ConnectionItem::updateGeometry);
  }

  m_out_node_item = (out_node_item && in_node_item) ? out_node_item : nullptr;
  m_in_node_item = (out_node_item && in_node_item) ? in_node_item : nullptr;

  if (m_out_node_item && m_in_node_item) {
    connect(m_out_node_item, &NodeItem::xChanged, this,
            &ConnectionItem::updateGeometry);
    connect(m_out_node_item, &NodeItem::yChanged, this,
            &ConnectionItem::updateGeometry);

    connect(m_in_node_item, &NodeItem::xChanged, this,
            &ConnectionItem::updateGeometry);
    connect(m_in_node_item, &NodeItem::yChanged, this,
            &ConnectionItem::updateGeometry);
  }
}

void ConnectionItem::updateGeometry() {
  m_connection_geometry.recalculate();

  update();
}

void ConnectionItem::updateVisibility() {
  auto out_node = m_out_node_item->getNode();
  auto in_node = m_in_node_item->getNode();
  auto connection = getConnection();

  auto out_node_visible = out_node->isVisible();
  auto in_node_visible = in_node->isVisible();
  auto connection_visible = connection->isVisible();

  setVisible(out_node_visible && in_node_visible && connection_visible);
}

}  // namespace flow_document