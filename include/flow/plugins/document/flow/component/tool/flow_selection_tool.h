#ifndef FLOW_FLOW_SELECTION_TOOL_H
#define FLOW_FLOW_SELECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/tool/flow_abstract_tool.h"
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

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

private:
  std::unique_ptr<FlowAbstractAction> m_action;
  Qt::MouseButtons m_mouse_button;
  QPointF m_mouse_click_pos;
};

#endif//FLOW_FLOW_SELECTION_TOOL_H
