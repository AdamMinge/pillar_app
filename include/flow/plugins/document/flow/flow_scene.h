#ifndef PLUGIN_FLOW_FLOW_SCENE_H
#define PLUGIN_FLOW_FLOW_SCENE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
#include <QMap>
#include <QMimeData>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}

class FlowDocument;
class FlowNodeItem;
class FlowAbstractTool;

class FLOW_DOCUMENT_API FlowScene : public QGraphicsScene
{
  Q_OBJECT

public:
  explicit FlowScene(QObject *parent = nullptr);
  ~FlowScene() override;

  void setSceneDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getSceneDocument() const;

  void setTool(FlowAbstractTool *tool);
  [[nodiscard]] FlowAbstractTool *getTool() const;

protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private Q_SLOTS:
  void nodeAdded(flow::node::Node *node);
  void nodeRemoved(flow::node::Node *node);

private:
  bool isAcceptable(const QMimeData *mime_data) const;

private:
  FlowDocument *m_flow_document;
  FlowAbstractTool *m_flow_tool;
  QMap<flow::node::Node *, FlowNodeItem *> m_node_items;
};

#endif//PLUGIN_FLOW_FLOW_SCENE_H
