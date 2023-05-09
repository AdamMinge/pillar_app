/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_scene.h"

#include "flow_document/component/scene/item/graphics_item.h"
#include "flow_document/component/scene/tool/abstract_tool.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsSceneDragDropEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowScene::FlowScene(QObject *parent)
    : QGraphicsScene(parent), m_flow_document(nullptr), m_tool(nullptr) {
  setItemIndexMethod(QGraphicsScene::NoIndex);
}

FlowScene::~FlowScene() = default;

void FlowScene::setDocument(FlowDocument *flow_document) {
  if (m_flow_document == flow_document) return;

  if (m_flow_document) {
    disconnect(m_flow_document,
               qOverload<const ChangeEvent &>(&FlowDocument::event), this,
               qOverload<const ChangeEvent &>(&FlowScene::onEvent));
  }

  m_flow_document = flow_document;

  if (m_flow_document) {
    connect(m_flow_document,
            qOverload<const ChangeEvent &>(&FlowDocument::event), this,
            qOverload<const ChangeEvent &>(&FlowScene::onEvent));
  }
}

FlowDocument *FlowScene::getDocument() const { return m_flow_document; }

void FlowScene::setTool(AbstractTool *tool) {
  if (m_tool) m_tool->deactivate();

  m_tool = tool;

  if (m_tool) m_tool->activate(this);
}

AbstractTool *FlowScene::getTool() const { return m_tool; }

QList<GraphicsItem *> FlowScene::hoveredItems() { return m_hovered_items; }

QPainterPath FlowScene::hoveredArea() const { return m_hovered_area; }

void FlowScene::setHoveredArea(const QPainterPath &path,
                               Qt::ItemSelectionOperation selectionOperation,
                               Qt::ItemSelectionMode mode) {
  auto hovered_items = QList<GraphicsItem *>{};
  auto items_in_area = items(path, mode);
  for (auto item : items_in_area) {
    if (auto hovered_item = dynamic_cast<GraphicsItem *>(item); hovered_item)
      hovered_items.append(hovered_item);
  }

  switch (selectionOperation) {
    case Qt::ReplaceSelection: {
      auto hover_items = [](auto &items, auto hovered) {
        for (auto item : items) {
          if (auto hovered_item = dynamic_cast<GraphicsItem *>(item);
              hovered_item)
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
  // TODO
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

void FlowScene::onEvent(const ChangeEvent &event) {
  switch (event.getType()) {}
  // TODO
}

bool FlowScene::isAcceptable(const QMimeData *mime_data) const {
  // TODO
  return false;
}

}  // namespace flow_document