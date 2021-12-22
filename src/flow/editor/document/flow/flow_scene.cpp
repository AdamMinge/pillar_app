/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_scene.h"
/* -------------------------------------------------------------------------- */

FlowScene::FlowScene(QObject *parent)
    : QGraphicsScene(parent),
      m_flow_document(nullptr)
{
}

FlowScene::~FlowScene() = default;

void FlowScene::setSceneDocument(FlowDocument *flow_document)
{
  if (m_flow_document == flow_document)
    return;

  m_flow_document = flow_document;
}

FlowDocument *FlowScene::getSceneDocument() const
{
  return m_flow_document;
}
