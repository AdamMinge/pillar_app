#ifndef FLOW_FLOW_SELECTION_TOOL_H
#define FLOW_FLOW_SELECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/tool/flow_abstract_tool.h"
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowItem;
class SelectionRectangle;

class FLOW_DOCUMENT_API FlowSelectionTool : public FlowAbstractTool
{
  Q_OBJECT

public:
  explicit FlowSelectionTool(QObject *parent = nullptr);
  ~FlowSelectionTool() override;

  void activate(FlowScene *scene) override;
  void deactivate(FlowScene *scene) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

  void mouseMoved(QGraphicsSceneMouseEvent *event) override;
  void mousePressed(QGraphicsSceneMouseEvent *event) override;
  void mouseReleased(QGraphicsSceneMouseEvent *event) override;

protected:
  void updateHover(const QPointF &mouse_pos);

  void startSceneMoving();
  void startItemMoving();
  void startItemSelection();

  void updateSceneMoving(const QPointF &mouse_pos);
  void updateItemMoving(const QPointF &mouse_pos);
  void updateItemSelection(const QPointF &mouse_pos);

  void endSceneMoving();
  void endItemMoving();
  void endItemSelection();

  void refreshCursor();

private:
  enum class Action;

private:
  Action m_action;

  FlowScene *m_scene;
  QPointF m_mouse_clicked_pos;
  Qt::MouseButton m_mouse_clicked_button;
  Qt::KeyboardModifiers m_modifiers;
  QGraphicsItem *m_clicked_item;

  std::unique_ptr<SelectionRectangle> m_selection_rect;
  QList<std::pair<QGraphicsItem *, QPointF>> m_moving_items;
};

enum class FlowSelectionTool::Action
{
  NoAction,
  SceneMoving,
  ItemMoving,
  ItemSelection
};

#endif//FLOW_FLOW_SELECTION_TOOL_H
