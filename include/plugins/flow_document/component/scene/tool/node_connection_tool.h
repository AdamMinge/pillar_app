#ifndef FLOW_DOCUMENT_NODE_CONNECTION_TOOL_H
#define FLOW_DOCUMENT_NODE_CONNECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/tool.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeItem;

class FLOW_DOCUMENT_API NodeConnectionTool : public Tool {
  Q_OBJECT

 public:
  explicit NodeConnectionTool(QObject *parent = nullptr);
  ~NodeConnectionTool() override;

  void activate(FlowScene *scene) override;
  void deactivate() override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

  void mouseMoved(QGraphicsSceneMouseEvent *event) override;
  void mousePressed(QGraphicsSceneMouseEvent *event) override;
  void mouseReleased(QGraphicsSceneMouseEvent *event) override;

 protected:
  void startConnectionCreating(NodeItem *node_item);
  void updateConnectionCreating(const QPointF &mouse_pos);
  void endConnectionCreating();

  void refreshCursor();

 private:
  enum class Action;

 private:
  Action m_action;
  Qt::KeyboardModifiers m_modifiers;
};

enum class NodeConnectionTool::Action { NoAction, ConnectionCreating };

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_CONNECTION_TOOL_H
