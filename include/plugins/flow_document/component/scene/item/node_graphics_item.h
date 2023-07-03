#ifndef FLOW_DOCUMENT_NODE_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_NODE_GRAPHICS_ITEM_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"
#include "flow_document/export.h"
#include "flow_document/flow/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodesChangeEvent;
class FlowDocument;
class ChangeEvent;
class NodePainter;
class NodeGeometry;
class Node;

/* --------------------------- NodeGraphicsItem ------------------------- */

class FLOW_DOCUMENT_API NodeGraphicsItem : public GraphicsItem {
  Q_OBJECT

 public:
  explicit NodeGraphicsItem(Node *node, FlowDocument *document,
                            QGraphicsItem *parent);
  ~NodeGraphicsItem() override;

  [[nodiscard]] Node *getNode() const;

  [[nodiscard]] const NodePainter *getPainter() const;
  [[nodiscard]] const NodeGeometry *getGeometry() const;

  [[nodiscard]] QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private Q_SLOTS:
  void onEvent(const ChangeEvent &event) override;
  void onUpdate(const NodesChangeEvent &event);

 private:
  std::unique_ptr<NodePainter> m_node_painter;
  std::unique_ptr<NodeGeometry> m_node_geometry;
};

/* ----------------------------- NodeGeometry --------------------------- */

class FLOW_DOCUMENT_API NodeGeometry {
  using PinToPos = QMap<std::pair<Pin::Type, int>, QPointF>;

 public:
  explicit NodeGeometry(const NodeGraphicsItem &node_item);
  virtual ~NodeGeometry();

  void recalculate();

  [[nodiscard]] QRectF getBoundingRect() const;
  [[nodiscard]] QPointF getLabelPosition() const;
  [[nodiscard]] QPointF getPinPosition(Pin::Type type, int index) const;
  [[nodiscard]] QPointF getPinLabelPosition(Pin::Type type, int index) const;
  [[nodiscard]] QPointF getWidgetPosition() const;

 private:
  [[nodiscard]] QSizeF calculateLabelSize() const;
  [[nodiscard]] QSizeF calculateWidgetSize() const;
  [[nodiscard]] QSizeF calculatePinsSize() const;
  [[nodiscard]] float calculatePinsWidth(Pin::Type type) const;

  [[nodiscard]] QPointF calculateLabelPosition() const;
  [[nodiscard]] PinToPos calculatePinPositions() const;
  [[nodiscard]] QPointF calculateWidgetPosition() const;

 private:
  const NodeGraphicsItem &m_node_item;
  QSizeF m_size;
  QPointF m_label_position;
  PinToPos m_pin_positions;
  QPointF m_widget_position;
};

/* ------------------------------ NodePainter --------------------------- */

class FLOW_DOCUMENT_API NodePainter {
 public:
  explicit NodePainter(const NodeGraphicsItem &node_item);
  virtual ~NodePainter();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option);

 private:
  void paintNodeRect(QPainter *painter, const QStyleOptionGraphicsItem *option);
  void paintNodeLabel(QPainter *painter,
                      const QStyleOptionGraphicsItem *option);
  void paintNodePins(QPainter *painter, const QStyleOptionGraphicsItem *option);
  void paintNodePinLabels(QPainter *painter,
                          const QStyleOptionGraphicsItem *option);

 private:
  const NodeGraphicsItem &m_node_item;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_GRAPHICS_ITEM_H
