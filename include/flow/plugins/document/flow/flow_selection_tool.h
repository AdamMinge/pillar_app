#ifndef FLOW_FLOW_SELECTION_TOOL_H
#define FLOW_FLOW_SELECTION_TOOL_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
#include "flow/plugins/document/flow/flow_abstract_tool.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowSelectionTool : public FlowAbstractTool
{
  Q_OBJECT

public:
  explicit FlowSelectionTool(QObject *parent = nullptr);
  ~FlowSelectionTool() override;

  void activate(FlowScene *scene) override;
  void deactivate(FlowScene *scene) override;

  void mousePressed(QGraphicsSceneMouseEvent *event) override;
  void mouseReleased(QGraphicsSceneMouseEvent *event) override;
};

#endif//FLOW_FLOW_SELECTION_TOOL_H
