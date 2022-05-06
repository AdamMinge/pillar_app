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

  void mouseMoved(QGraphicsSceneMouseEvent *event) override;
  void mousePressed(QGraphicsSceneMouseEvent *event) override;
  void mouseReleased(QGraphicsSceneMouseEvent *event) override;

protected:
  void updateHover(QGraphicsSceneMouseEvent *event);

  void startSceneMoving(QGraphicsSceneMouseEvent *event);
  void startItemMoving(QGraphicsSceneMouseEvent *event);
  void startItemSelection(QGraphicsSceneMouseEvent *event);

  void updateSceneMoving(QGraphicsSceneMouseEvent *event);
  void updateItemMoving(QGraphicsSceneMouseEvent *event);
  void updateItemSelection(QGraphicsSceneMouseEvent *event);

  void endSceneMoving(QGraphicsSceneMouseEvent *event);
  void endItemMoving(QGraphicsSceneMouseEvent *event);
  void endItemSelection(QGraphicsSceneMouseEvent *event);

private:
  enum class Action;

private:
  Action m_action;

  QPointF m_mouse_clicked_pos;
  Qt::MouseButton m_mouse_clicked_button;
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
