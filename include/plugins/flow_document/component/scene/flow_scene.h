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

class GraphicsItem;
class FlowDocument;
class AbstractTool;

class FlowGraphicsItem;

class FLOW_DOCUMENT_API FlowScene : public QGraphicsScene {
  Q_OBJECT

 public:
  explicit FlowScene(QObject *parent = nullptr);
  ~FlowScene() override;

  void setDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getDocument() const;

  void setTool(AbstractTool *tool);
  [[nodiscard]] AbstractTool *getTool() const;

  [[nodiscard]] QList<GraphicsItem *> hoveredItems();
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

 private:
  bool isAcceptable(const QMimeData *mime_data) const;

 private:
  FlowDocument *m_flow_document;
  AbstractTool *m_tool;

  QPainterPath m_hovered_area;
  QList<GraphicsItem *> m_hovered_items;

  FlowGraphicsItem *m_flow_item;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_SCENE_H
