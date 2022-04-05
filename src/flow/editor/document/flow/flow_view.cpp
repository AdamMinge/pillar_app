/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_view.h"
#include "flow/editor/document/flow/flow_scene.h"
/* -------------------------------------------------------------------------- */

FlowView::FlowView(QWidget *parent) : QGraphicsView(parent) {}

FlowView::~FlowView() = default;

void FlowView::setScene(FlowScene *scene) { QGraphicsView::setScene(scene); }

FlowScene *FlowView::getScene() const
{
  auto flow_scene = dynamic_cast<FlowScene *>(scene());
  Q_ASSERT(flow_scene || !scene());

  return flow_scene;
}
