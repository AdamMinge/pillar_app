#ifndef FLOW_DOCUMENT_NODE_ITEM_H
#define FLOW_DOCUMENT_NODE_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsProxyWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_item.h"
#include "flow_document/export.h"
#include "flow_document/flow/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeSelectionItem;
class NodesChangeEvent;
class FlowDocument;
class ChangeEvent;
class NodeItem;
class Node;

/* ----------------------------- NodeGeometry --------------------------- */

class FLOW_DOCUMENT_API NodeGeometry {
  using PinToPos = QMap<std::pair<Pin::Type, int>, QPointF>;

 public:
  using FoundPin = std::optional<std::pair<int, Pin::Type>>;

 public:
  explicit NodeGeometry(const NodeItem &node_item);
  ~NodeGeometry();

  void recalculate();

  [[nodiscard]] QRectF getBoundingRect() const;
  [[nodiscard]] QPointF getLabelPosition() const;
  [[nodiscard]] QPointF getPinPosition(Pin::Type type, int index) const;
  [[nodiscard]] QPointF getPinLabelPosition(Pin::Type type, int index) const;
  [[nodiscard]] QPointF getEmbeddedWidgetPosition() const;

  [[nodiscard]] FoundPin findNearestPin(
      const QPointF &search_pos, qreal search_scale,
      std::optional<Pin::Type> type = {}) const;

 private:
  [[nodiscard]] QSizeF calculateLabelSize() const;
  [[nodiscard]] QSizeF calculateEmbeddedWidgetSize() const;
  [[nodiscard]] QSizeF calculatePinsSize() const;
  [[nodiscard]] qreal calculatePinsWidth(Pin::Type type) const;

  [[nodiscard]] QPointF calculateLabelPosition(const QRectF &rect,
                                               const QSizeF &label) const;
  [[nodiscard]] PinToPos calculatePinPositions(const QRectF &rect,
                                               const QSizeF &label) const;
  [[nodiscard]] QPointF calculateEmbeddedWidgetPosition(
      const QRectF &rect, const QSizeF &size) const;

 private:
  const NodeItem &m_node_item;
  QRectF m_rect;
  QPointF m_label_position;
  PinToPos m_pin_positions;
  QPointF m_embedded_widget_position;
};

/* ------------------------------ NodePainter --------------------------- */

class FLOW_DOCUMENT_API NodePainter {
 public:
  explicit NodePainter(const NodeItem &node_item);
  ~NodePainter();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option);

 private:
  void paintNodeRect(QPainter *painter, const QStyleOptionGraphicsItem *option);
  void paintNodeLabel(QPainter *painter,
                      const QStyleOptionGraphicsItem *option);
  void paintNodePins(QPainter *painter, const QStyleOptionGraphicsItem *option);
  void paintNodePinLabels(QPainter *painter,
                          const QStyleOptionGraphicsItem *option);

 private:
  const NodeItem &m_node_item;
};

/* ------------------------------- NodeItem ----------------------------- */

class FLOW_DOCUMENT_API NodeItem : public ObjectItem {
  Q_OBJECT

 public:
  explicit NodeItem(Node *node, FlowDocument *document, QGraphicsItem *parent);
  ~NodeItem() override;

  [[nodiscard]] Node *getNode() const;

  [[nodiscard]] const NodePainter &getPainter() const;
  [[nodiscard]] const NodeGeometry &getGeometry() const;

  [[nodiscard]] QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private Q_SLOTS:
  void onSceneChanged() override;
  void onEvent(const ChangeEvent &event) override;
  void onUpdate(const NodesChangeEvent &event);

  void embedWidget();
  void updateGeometry();

 private:
  NodeSelectionItem *m_selection_item;
  NodePainter m_node_painter;
  NodeGeometry m_node_geometry;
  QGraphicsProxyWidget *m_proxy_widget;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_ITEM_H
