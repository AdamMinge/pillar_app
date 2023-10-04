/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/node_connection_tool.h"

#include "flow_document/command/add_remove_connection.h"
#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/item/cubic_path_item.h"
#include "flow_document/component/scene/item/node_item.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Utils -------------------------------- */

namespace {

constexpr qreal SEARCH_SCALE = 25.0;

}

/* ---------------------------- NodeConnectionTool -------------------------- */

NodeConnectionTool::NodeConnectionTool(QObject *parent)
    : Tool(tr("Node Connection Tool"), QIcon(icons::x32::ConnectionTool),
           QKeySequence(Qt::Key_C), parent),
      m_action(Action::NoAction),
      m_clicked_item(nullptr),
      m_cubic_path(std::make_unique<CubicPathItem>()) {}

NodeConnectionTool::~NodeConnectionTool() = default;

void NodeConnectionTool::activate(FlowScene *scene) { Tool::activate(scene); }

void NodeConnectionTool::deactivate() { Tool::deactivate(); }

void NodeConnectionTool::keyPressEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void NodeConnectionTool::keyReleaseEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void NodeConnectionTool::mouseMoved(QGraphicsSceneMouseEvent *event) {
  Tool::mouseMoved(event);

  const auto mouse_pos = event->scenePos();

  if (m_action == Action::NoAction &&
      m_mouse_clicked_button == Qt::LeftButton) {
    auto drag_distance = (m_mouse_clicked_pos - mouse_pos).manhattanLength();
    if (drag_distance >= QApplication::startDragDistance() / 2.0) {
      tryStartConnectionCreating(mouse_pos);
    }
  }

  switch (m_action) {
    case Action::ConnectionCreating: {
      updateConnectionCreating(mouse_pos);
      break;
    }

    default:
      break;
  }

  refreshCursor();
}

void NodeConnectionTool::mousePressed(QGraphicsSceneMouseEvent *event) {
  Tool::mousePressed(event);

  if (m_action != Action::NoAction) return;

  switch (event->button()) {
    case Qt::LeftButton: {
      m_mouse_clicked_button = Qt::LeftButton;
      m_mouse_clicked_pos = event->scenePos();

      if (auto scene = getScene(); scene) {
        auto item = scene->itemAt(event->scenePos(), QTransform{});
        auto node_item = dynamic_cast<NodeItem *>(item);
        if (node_item) m_clicked_item = node_item;
      }

      break;
    }

    default:
      break;
  }

  refreshCursor();
}

void NodeConnectionTool::mouseReleased(QGraphicsSceneMouseEvent *event) {
  Tool::mouseReleased(event);

  const auto mouse_pos = event->scenePos();

  switch (m_action) {
    case Action::ConnectionCreating:
      endConnectionCreating(mouse_pos);
      break;
  }

  m_action = Action::NoAction;
  m_mouse_clicked_pos = QPointF{};
  m_mouse_clicked_button = Qt::MouseButton{};
  m_clicked_item = nullptr;

  refreshCursor();
}

void NodeConnectionTool::startConnectionCreating(
    NodeItem *node_item, const std::pair<int, Pin::Type> &found_pin) {
  auto scene = getScene();
  Q_ASSERT(scene);

  const auto pin_type = found_pin.second;
  const auto pin_index = found_pin.first;

  m_action = Action::ConnectionCreating;

  m_new_connection = Connection{};
  if (pin_type == Pin::Type::Out) {
    m_new_connection.setOutputSide(
        ConnectionSide(node_item->getNode()->getId(), pin_index));
  } else {
    m_new_connection.setInputSide(
        ConnectionSide(node_item->getNode()->getId(), pin_index));
  }

  const auto pos =
      node_item->getGeometry().getPinPosition(pin_type, pin_index) +
      node_item->pos();

  const auto start_pos = pin_type == Pin::Type::Out ? pos : m_mouse_clicked_pos;
  const auto end_pos = pin_type == Pin::Type::Out ? m_mouse_clicked_pos : pos;

  m_cubic_path->setStartPos(start_pos);
  m_cubic_path->setEndPos(end_pos);

  scene->addItem(m_cubic_path.get());
}

void NodeConnectionTool::updateConnectionCreating(const QPointF &mouse_pos) {
  auto output_side = m_new_connection.getOutputSide();
  if (output_side.isNull()) {
    m_cubic_path->setStartPos(mouse_pos);
  } else {
    m_cubic_path->setEndPos(mouse_pos);
  }
}

void NodeConnectionTool::endConnectionCreating(const QPointF &mouse_pos) {
  if (auto scene = getScene(); scene) {
    tryCreateNewConnection(mouse_pos);
    scene->removeItem(m_cubic_path.get());
  }
}

void NodeConnectionTool::tryStartConnectionCreating(const QPointF &mouse_pos) {
  if (!m_clicked_item) return;

  const auto search_pos = mouse_pos - m_clicked_item->pos();
  const auto opt_found_pin =
      m_clicked_item->getGeometry().findNearestPin(search_pos, SEARCH_SCALE);
  if (!opt_found_pin.has_value()) return;

  const auto node = m_clicked_item->getNode();
  const auto node_layer = node->getParent();
  const auto found_pin = opt_found_pin.value();
  const auto connection_side = ConnectionSide(node->getId(), found_pin.first);
  if (!node_layer->canConnect(connection_side, found_pin.second)) return;

  startConnectionCreating(m_clicked_item, found_pin);
}

void NodeConnectionTool::tryCreateNewConnection(const QPointF &mouse_pos) {
  auto scene = getScene();
  Q_ASSERT(scene);

  auto item = scene->itemAt(mouse_pos, QTransform{});
  auto node_item = dynamic_cast<NodeItem *>(item);
  if (!node_item) return;

  const auto search_pos = mouse_pos - node_item->pos();
  const auto opt_found_pin =
      node_item->getGeometry().findNearestPin(search_pos, SEARCH_SCALE);
  if (!opt_found_pin.has_value()) return;

  const auto node = node_item->getNode();
  const auto node_layer = node->getParent();
  const auto found_pin = opt_found_pin.value();
  const auto pin_type = found_pin.second;
  const auto pin_index = found_pin.first;

  if (pin_type == Pin::Type::Out) {
    m_new_connection.setOutputSide(ConnectionSide(node->getId(), pin_index));
    m_new_connection.setName(
        createNewConnectionName(m_new_connection, node_item, m_clicked_item));
  } else {
    m_new_connection.setInputSide(ConnectionSide(node->getId(), pin_index));
    m_new_connection.setName(
        createNewConnectionName(m_new_connection, m_clicked_item, node_item));
  }

  if (!node_layer->canConnect(m_new_connection.getOutputSide(),
                              m_new_connection.getInputSide()))
    return;

  auto entires = std::list<ConnectionEntry>{};
  entires.emplace_back(ConnectionEntry{
      node_layer, std::make_unique<Connection>(m_new_connection),
      node_layer->connectionsCount()});

  auto document = getDocument();
  document->getUndoStack()->push(
      new AddConnections(document, std::move(entires)));
}

void NodeConnectionTool::refreshCursor() {
  Qt::CursorShape cursor_shape = Qt::ArrowCursor;

  switch (m_action) {
    default:
      break;
  }

  setCursor(cursor_shape);
}

QString NodeConnectionTool::createNewConnectionName(
    const Connection &connection, NodeItem *output, NodeItem *input) const {
  return QString("%1[%2] -> %3[%4]")
      .arg(output->getNode()->getName(),
           output->getNode()
               ->getPin(Pin::Type::Out, connection.getOutputSide().getPinId())
               .getCaption(),
           input->getNode()->getName(),
           input->getNode()
               ->getPin(Pin::Type::In, connection.getInputSide().getPinId())
               .getCaption());
}

}  // namespace flow_document