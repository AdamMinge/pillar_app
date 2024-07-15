#ifndef FLOW_DOCUMENT_NODE_CONNECTION_TOOL_H
#define FLOW_DOCUMENT_NODE_CONNECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/tool.h"
#include "flow_document/export.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeItem;
class CubicPathItem;

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
  void startConnectionCreating(NodeItem *node_item,
                               const std::pair<int, Pin::Type> &found_pin);
  void updateConnectionCreating(const QPointF &mouse_pos);
  void endConnectionCreating(const QPointF &mouse_pos);

  void tryStartConnectionCreating(const QPointF &mouse_pos);
  void tryCreateNewConnection(const QPointF &mouse_pos);

  void refreshCursor();

 private:
  [[nodiscard]] QString createNewConnectionName(const Connection &connection,
                                                NodeItem *output,
                                                NodeItem *input) const;

 private:
  enum class Action;

 private:
  Action m_action;

  QPointF m_mouse_clicked_pos;
  Qt::MouseButton m_mouse_clicked_button;
  Qt::KeyboardModifiers m_modifiers;
  NodeItem *m_clicked_item;

  std::unique_ptr<CubicPathItem> m_cubic_path;
  Connection m_new_connection;
};

enum class NodeConnectionTool::Action { NoAction, ConnectionCreating };

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_CONNECTION_TOOL_H
