/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_scene.h"

#include "flow_document/command/add_remove_node.h"
#include "flow_document/component/scene/flow_abstract_tool.h"
#include "flow_document/component/scene/flow_item.h"
#include "flow_document/component/scene/flow_node_item.h"
#include "flow_document/event/objects_event.h"
#include "flow_document/flow_document.h"
#include "flow_document/node/node.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsSceneDragDropEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowScene::FlowScene(QObject *parent)
    : QGraphicsScene(parent), m_flow_document(nullptr), m_flow_tool(nullptr) {
  setItemIndexMethod(QGraphicsScene::NoIndex);
}

FlowScene::~FlowScene() = default;

void FlowScene::setSceneDocument(FlowDocument *flow_document) {
  if (m_flow_document == flow_document) return;

  if (m_flow_document) {
    disconnect(m_flow_document,
               qOverload<const ObjectsAddedEvent &>(&FlowDocument::event), this,
               qOverload<const ObjectsAddedEvent &>(&FlowScene::onEvent));
    disconnect(m_flow_document,
               qOverload<const ObjectsRemovedEvent &>(&FlowDocument::event),
               this,
               qOverload<const ObjectsRemovedEvent &>(&FlowScene::onEvent));
  }

  m_flow_document = flow_document;

  if (m_flow_document) {
    connect(m_flow_document,
            qOverload<const ObjectsAddedEvent &>(&FlowDocument::event), this,
            qOverload<const ObjectsAddedEvent &>(&FlowScene::onEvent));
    connect(m_flow_document,
            qOverload<const ObjectsRemovedEvent &>(&FlowDocument::event), this,
            qOverload<const ObjectsRemovedEvent &>(&FlowScene::onEvent));
  }
}

FlowDocument *FlowScene::getSceneDocument() const { return m_flow_document; }

void FlowScene::setTool(FlowAbstractTool *tool) {
  if (m_flow_tool) m_flow_tool->deactivate();

  m_flow_tool = tool;

  if (m_flow_tool) m_flow_tool->activate(this);
}

FlowAbstractTool *FlowScene::getTool() const { return m_flow_tool; }

QList<FlowItem *> FlowScene::hoveredItems() { return m_hovered_items; }

QPainterPath FlowScene::hoveredArea() const { return m_hovered_area; }

void FlowScene::setHoveredArea(const QPainterPath &path,
                               Qt::ItemSelectionOperation selectionOperation,
                               Qt::ItemSelectionMode mode) {
  auto hovered_items = QList<FlowItem *>{};
  auto items_in_area = items(path, mode);
  for (auto item : items_in_area) {
    if (auto hovered_item = dynamic_cast<FlowItem *>(item); hovered_item)
      hovered_items.append(hovered_item);
  }

  switch (selectionOperation) {
    case Qt::ReplaceSelection: {
      auto hover_items = [](auto &items, auto hovered) {
        for (auto item : items) {
          if (auto hovered_item = dynamic_cast<FlowItem *>(item); hovered_item)
            hovered_item->setHovered(hovered);
        }
      };

      hover_items(m_hovered_items, false);

      m_hovered_area = path;
      m_hovered_items = std::move(hovered_items);

      hover_items(m_hovered_items, true);
    } break;

    case Qt::AddToSelection: {
      m_hovered_area.addPath(path);
      m_hovered_items.append(std::move(hovered_items));
    } break;
  }
}

void FlowScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  auto mime_data = event->mimeData();
  event->setAccepted(isAcceptable(mime_data));
}

void FlowScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
  auto mime_data = event->mimeData();
  event->setAccepted(isAcceptable(mime_data));
}

void FlowScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
  auto mime_data = event->mimeData();
  if (mime_data->hasFormat(QLatin1String("flow/node"))) {
    const auto data = mime_data->data(QLatin1String("flow/node"));
    for (auto &node_id : data.split(';'))
      m_flow_document->getUndoStack()->push(
          new AddNodeCommand(m_flow_document, node_id, event->scenePos()));

  } else if (mime_data->hasFormat(QLatin1String("flow/type_converter"))) {
    // TODO Implementation
  }
}

void FlowScene::keyPressEvent(QKeyEvent *event) {
  QGraphicsScene::keyPressEvent(event);
  if (m_flow_tool) m_flow_tool->keyPressEvent(event);
}

void FlowScene::keyReleaseEvent(QKeyEvent *event) {
  QGraphicsScene::keyReleaseEvent(event);
  if (m_flow_tool) m_flow_tool->keyReleaseEvent(event);
}

void FlowScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_flow_tool) {
    mouseEvent->accept();
    m_flow_tool->mouseMoved(mouseEvent);
  }
}

void FlowScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_flow_tool) {
    mouseEvent->accept();
    m_flow_tool->mousePressed(mouseEvent);
  }
}

void FlowScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_flow_tool) {
    mouseEvent->accept();
    m_flow_tool->mouseReleased(mouseEvent);
  }
}

void FlowScene::onEvent(const ObjectsAddedEvent &event) {
  for (auto object : event.getObjects()) {
    if (event.getObjectsType() == ObjectsAddedEvent::ObjectsType::Node) {
      auto node = dynamic_cast<Node *>(object);
      Q_ASSERT(node && !m_node_items.contains(node));

      auto node_item = std::make_unique<FlowNodeItem>(m_flow_document, node);
      m_node_items.insert(node, node_item.get());
      addItem(node_item.release());
    }
  }
}

void FlowScene::onEvent(const ObjectsRemovedEvent &event) {
  for (auto object : event.getObjects()) {
    if (event.getObjectsType() == ObjectsAddedEvent::ObjectsType::Node) {
      auto node = dynamic_cast<Node *>(object);
      Q_ASSERT(node && m_node_items.contains(node));

      removeItem(m_node_items[node]);
      m_node_items.remove(node);
    }
  }
}

bool FlowScene::isAcceptable(const QMimeData *mime_data) const {
  if (mime_data->hasFormat(QLatin1String("flow/node")) ||
      mime_data->hasFormat(QLatin1String("flow/type_converter")))
    return true;

  return false;
}

}  // namespace flow_document