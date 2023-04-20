#ifndef PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H
#define PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMap>
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowNodeItem;
struct NodeStyles;

class FLOW_DOCUMENT_API FlowNodeGeometry {
  using PinToPos = QMap<std::pair<Pin::Type, int>, QPointF>;

 public:
  explicit FlowNodeGeometry(const FlowNodeItem &node_item);
  virtual ~FlowNodeGeometry();

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
  const FlowNodeItem &m_node_item;
  QSizeF m_size;
  QPointF m_label_position;
  PinToPos m_pin_positions;
  QPointF m_widget_position;
};

}  // namespace flow_document

#endif  // PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H
