#ifndef FLOW_DOCUMENT_NODE_SELECTION_TOOL_H
#define FLOW_DOCUMENT_NODE_SELECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/tool/tool.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class SelectionRectangle;
class NodeItem;
class Node;

class LIB_FLOW_DOCUMENT_API NodeSelectionTool : public Tool {
  Q_OBJECT

 public:
  explicit NodeSelectionTool(QObject *parent = nullptr);
  ~NodeSelectionTool() override;

  void activate(FlowScene *scene) override;
  void deactivate() override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

  void mouseMoved(QGraphicsSceneMouseEvent *event) override;
  void mousePressed(QGraphicsSceneMouseEvent *event) override;
  void mouseReleased(QGraphicsSceneMouseEvent *event) override;

 protected:
  void updateHover(const QPointF &mouse_pos);

  void startItemMoving();
  void startItemSelection();

  void updateItemMoving(const QPointF &mouse_pos);
  void updateItemSelection(const QPointF &mouse_pos);

  void endItemMoving();
  void endItemSelection();

  void refreshCursor();

 private:
  enum class Action;

 private:
  void selectNodes(const QList<QGraphicsItem *> items, bool extend = true);
  void unselectNodes(const QList<QGraphicsItem *> items);

  [[nodiscard]] QList<Node *> getNodes(
      const QList<QGraphicsItem *> items) const;

  [[nodiscard]] bool isAnyNodeSelected() const;
  [[nodiscard]] bool isAnyNodeHovered() const;

 private:
  Action m_action;

  QPointF m_mouse_clicked_pos;
  Qt::MouseButton m_mouse_clicked_button;
  Qt::KeyboardModifiers m_modifiers;
  NodeItem *m_clicked_item;

  std::unique_ptr<SelectionRectangle> m_selection_rect;
  QList<std::pair<Node *, QPointF>> m_moving_nodes;
};

enum class NodeSelectionTool::Action { NoAction, ItemMoving, ItemSelection };

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODE_SELECTION_TOOL_H
