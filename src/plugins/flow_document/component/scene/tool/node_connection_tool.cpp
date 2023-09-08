/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/node_connection_tool.h"

#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/item/node_item.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- NodeConnectionTool -------------------------- */

NodeConnectionTool::NodeConnectionTool(QObject *parent)
    : Tool(tr("Node Connection Tool"), QIcon(icons::x32::ConnectionTool),
           QKeySequence(Qt::Key_C), parent),
      m_action(Action::NoAction) {}

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

  switch (m_action) {
    case Action::ConnectionCreating: {
      const auto mouse_pos = event->scenePos();
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
      if (auto scene = getScene(); scene) {
        auto mouse_clicked_pos = event->scenePos();
        auto item = scene->itemAt(mouse_clicked_pos, QTransform{});
        auto node_item = dynamic_cast<NodeItem *>(item);

        if (node_item) {
          startConnectionCreating(node_item);
        }
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

  switch (m_action) {
    case Action::ConnectionCreating:
      endConnectionCreating();
      break;
  }

  m_action = Action::NoAction;

  refreshCursor();
}

void NodeConnectionTool::startConnectionCreating(NodeItem *node_item) {
  m_action = Action::ConnectionCreating;
}

void NodeConnectionTool::updateConnectionCreating(const QPointF &mouse_pos) {}

void NodeConnectionTool::endConnectionCreating() {}

void NodeConnectionTool::refreshCursor() {
  Qt::CursorShape cursor_shape = Qt::ArrowCursor;

  switch (m_action) {
    default:
      break;
  }

  setCursor(cursor_shape);
}

}  // namespace flow_document