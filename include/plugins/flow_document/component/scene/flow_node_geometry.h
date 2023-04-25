#ifndef FLOW_DOCUMENT_FLOW_NODE_GEOMETRY_H
#define FLOW_DOCUMENT_FLOW_NODE_GEOMETRY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMap>
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/flow_pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowNodeGraphicsItem;
struct NodeStyles;

class FLOW_DOCUMENT_API FlowNodeGeometry {
  using PinToPos = QMap<std::pair<FlowPin::Type, int>, QPointF>;

 public:
  explicit FlowNodeGeometry(const FlowNodeGraphicsItem &node_item);
  virtual ~FlowNodeGeometry();

  void recalculate();

  [[nodiscard]] QRectF getBoundingRect() const;
  [[nodiscard]] QPointF getLabelPosition() const;
  [[nodiscard]] QPointF getPinPosition(FlowPin::Type type, int index) const;
  [[nodiscard]] QPointF getPinLabelPosition(FlowPin::Type type,
                                            int index) const;
  [[nodiscard]] QPointF getWidgetPosition() const;

 private:
  [[nodiscard]] QSizeF calculateLabelSize() const;
  [[nodiscard]] QSizeF calculateWidgetSize() const;
  [[nodiscard]] QSizeF calculatePinsSize() const;
  [[nodiscard]] float calculatePinsWidth(FlowPin::Type type) const;

  [[nodiscard]] QPointF calculateLabelPosition() const;
  [[nodiscard]] PinToPos calculatePinPositions() const;
  [[nodiscard]] QPointF calculateWidgetPosition() const;

 private:
  const FlowNodeGraphicsItem &m_node_item;
  QSizeF m_size;
  QPointF m_label_position;
  PinToPos m_pin_positions;
  QPointF m_widget_position;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_NODE_GEOMETRY_H
