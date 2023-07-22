/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_scene.h"

#include "flow_document/component/scene/item/factory/item_factory.h"
#include "flow_document/component/scene/item/flow_item.h"
#include "flow_document/component/scene/item/object_item.h"
#include "flow_document/component/scene/tool/tool.h"
#include "flow_document/flow/factory/object_factory.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsSceneDragDropEvent>
#include <QIODevice>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowScene::FlowScene(QObject *parent)
    : QGraphicsScene(parent),
      m_flow_document(nullptr),
      m_tool(nullptr),
      m_scene_max_size(32767) {
  setItemIndexMethod(QGraphicsScene::NoIndex);
  setSceneRect(-m_scene_max_size, -m_scene_max_size, m_scene_max_size * 2,
               m_scene_max_size * 2);
}

FlowScene::~FlowScene() = default;

void FlowScene::setDocument(FlowDocument *flow_document) {
  if (m_flow_document == flow_document) return;

  m_flow_document = flow_document;

  clear();
  if (m_flow_document) {
    addItem(createItem<FlowItem>(m_flow_document->getFlow(), m_flow_document));
  }
}

FlowDocument *FlowScene::getDocument() const { return m_flow_document; }

void FlowScene::setTool(Tool *tool) {
  if (m_tool) m_tool->deactivate();

  m_tool = tool;

  if (m_tool) m_tool->activate(this);
}

Tool *FlowScene::getTool() const { return m_tool; }

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
  auto drop_position = event->scenePos();

  if (mime_data->hasFormat(mimetype::Factories)) {
    auto encoded_data = mime_data->data(mimetype::Factories);
    QDataStream stream(&encoded_data, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
      auto object_class = QString{};
      stream >> object_class;

      auto factory = getObjectFactoryByClassName(object_class);
      Q_ASSERT(factory);

      factory->addObject(m_flow_document, [&drop_position](Object *object) {
        if (object->isClassOrChild<MoveableObject>()) {
          auto moveable_object = static_cast<MoveableObject *>(object);
          moveable_object->setPosition(drop_position);
        }
      });
    }
  }
}

void FlowScene::keyPressEvent(QKeyEvent *event) {
  QGraphicsScene::keyPressEvent(event);
  if (m_tool) m_tool->keyPressEvent(event);
}

void FlowScene::keyReleaseEvent(QKeyEvent *event) {
  QGraphicsScene::keyReleaseEvent(event);
  if (m_tool) m_tool->keyReleaseEvent(event);
}

void FlowScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_tool) {
    mouseEvent->accept();
    m_tool->mouseMoved(mouseEvent);
  }
}

void FlowScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_tool) {
    mouseEvent->accept();
    m_tool->mousePressed(mouseEvent);
  }
}

void FlowScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_tool) {
    mouseEvent->accept();
    m_tool->mouseReleased(mouseEvent);
  }
}

bool FlowScene::isAcceptable(const QMimeData *mime_data) const {
  if (mime_data->hasFormat(mimetype::Factories)) {
    auto encoded_data = mime_data->data(mimetype::Factories);
    QDataStream stream(&encoded_data, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
      auto object_class = QString{};
      stream >> object_class;

      auto factory = getObjectFactoryByClassName(object_class);
      Q_ASSERT(factory);

      if (!factory->canAddObject(m_flow_document)) return false;
    }

    return true;
  }

  return false;
}

}  // namespace flow_document