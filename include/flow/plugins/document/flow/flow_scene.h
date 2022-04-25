#ifndef PLUGIN_FLOW_FLOW_SCENE_H
#define PLUGIN_FLOW_FLOW_SCENE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
#include <QMimeData>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowDocument;

class FLOW_DOCUMENT_API FlowScene : public QGraphicsScene
{
  Q_OBJECT

public:
  explicit FlowScene(QObject *parent = nullptr);
  ~FlowScene() override;

  void setSceneDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getSceneDocument() const;

protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  bool isAcceptable(const QMimeData *mime_data) const;

private:
  FlowDocument *m_flow_document;
};

#endif//PLUGIN_FLOW_FLOW_SCENE_H
