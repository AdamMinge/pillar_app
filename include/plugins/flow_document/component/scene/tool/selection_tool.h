#ifndef FLOW_DOCUMENT_SELECTION_TOOL_H
#define FLOW_DOCUMENT_SELECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/abstract_tool.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class SelectionRectangle;
class ObjectGraphicsItem;

class FLOW_DOCUMENT_API SelectionTool : public AbstractTool {
  Q_OBJECT

 public:
  explicit SelectionTool(QObject *parent = nullptr);
  ~SelectionTool() override;

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
  Action m_action;

  QPointF m_mouse_clicked_pos;
  Qt::MouseButton m_mouse_clicked_button;
  Qt::KeyboardModifiers m_modifiers;
  ObjectGraphicsItem *m_clicked_item;

  std::unique_ptr<SelectionRectangle> m_selection_rect;
  QList<std::pair<ObjectGraphicsItem *, QPointF>> m_moving_items;
};

enum class SelectionTool::Action { NoAction, ItemMoving, ItemSelection };

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_SELECTION_TOOL_H
