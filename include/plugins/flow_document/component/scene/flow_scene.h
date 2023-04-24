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

class Node;

class FlowItem;
class FlowNodeItem;
class FlowDocument;
class FlowAbstractTool;

class ChangeEvent;
class ObjectsAddedEvent;
class ObjectsRemovedEvent;

class FLOW_DOCUMENT_API FlowScene : public QGraphicsScene {
  Q_OBJECT

 public:
  explicit FlowScene(QObject *parent = nullptr);
  ~FlowScene() override;

  void setSceneDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getSceneDocument() const;

  void setTool(FlowAbstractTool *tool);
  [[nodiscard]] FlowAbstractTool *getTool() const;

  [[nodiscard]] QList<FlowItem *> hoveredItems();
  [[nodiscard]] QPainterPath hoveredArea() const;
  void setHoveredArea(
      const QPainterPath &path,
      Qt::ItemSelectionOperation selectionOperation = Qt::ReplaceSelection,
      Qt::ItemSelectionMode mode = Qt::IntersectsItemShape);

 protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

 private Q_SLOTS:
  void onEvent(const ChangeEvent &event);

 private:
  bool isAcceptable(const QMimeData *mime_data) const;

  void onObjectsAddedEvent(const ObjectsAddedEvent &event);
  void onObjectsRemovedEvent(const ObjectsRemovedEvent &event);

 private:
  FlowDocument *m_flow_document;
  FlowAbstractTool *m_flow_tool;

  QPainterPath m_hovered_area;
  QList<FlowItem *> m_hovered_items;

  QMap<Node *, FlowNodeItem *> m_node_items;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_SCENE_H
