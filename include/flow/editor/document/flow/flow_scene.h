#ifndef FLOW_FLOW_SCENE_H
#define FLOW_FLOW_SCENE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
/* -------------------------------------------------------------------------- */

class FlowDocument;

class FlowScene : public QGraphicsScene
{
  Q_OBJECT

public:
  explicit FlowScene(QObject *parent = nullptr);
  ~FlowScene() override;

  void setSceneDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getSceneDocument() const;

private:
  FlowDocument *m_flow_document;
};

#endif//FLOW_FLOW_SCENE_H
