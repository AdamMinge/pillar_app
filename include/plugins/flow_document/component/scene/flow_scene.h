#ifndef FLOW_DOCUMENT_FLOW_SCENE_H
#define FLOW_DOCUMENT_FLOW_SCENE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
#include <QMap>
#include <QMimeData>
#include <QPainterPath>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ObjectItem;
class FlowDocument;
class Tool;

class FlowItem;

class FLOW_DOCUMENT_API FlowScene : public QGraphicsScene {
  Q_OBJECT

 public:
  explicit FlowScene(QObject *parent = nullptr);
  ~FlowScene() override;

  void setDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getDocument() const;

  void setTool(Tool *tool);
  [[nodiscard]] Tool *getTool() const;

 protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

 private:
  bool isAcceptable(const QMimeData *mime_data) const;

 private:
  FlowDocument *m_flow_document;
  Tool *m_tool;
  const int m_scene_max_size;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_SCENE_H
