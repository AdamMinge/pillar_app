/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_selection_tool.h"
/* -------------------------------------------------------------------------- */

FlowSelectionTool::FlowSelectionTool(QObject *parent)
    : FlowAbstractTool(
        tr("Selection Tool"),
        QIcon(":/plugins/document/flow/images/32x32/selection_tool.png"),
        QCursor(), QKeySequence(), parent)
{}

FlowSelectionTool::~FlowSelectionTool() = default;

void FlowSelectionTool::activate(FlowScene *scene) {}

void FlowSelectionTool::deactivate(FlowScene *scene) {}

void FlowSelectionTool::mousePressed(QGraphicsSceneMouseEvent *event) {}

void FlowSelectionTool::mouseReleased(QGraphicsSceneMouseEvent *event) {}