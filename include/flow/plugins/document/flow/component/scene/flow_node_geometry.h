#ifndef PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H
#define PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMap>
#include <QPainter>
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/node/pin.h"
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowNodeItem;
struct NodeStyles;

class FLOW_DOCUMENT_API FlowNodeGeometry
{
  using PinToPos = QMap<std::pair<flow::node::Pin::Type, int>, QPointF>;

public:
  explicit FlowNodeGeometry(const FlowNodeItem &node_item);
  virtual ~FlowNodeGeometry();

  void recalculate();

  [[nodiscard]] QRectF getBoundingRect() const;
  [[nodiscard]] QPointF getLabelPosition() const;
  [[nodiscard]] QPointF
  getPinPosition(flow::node::Pin::Type type, int index) const;
  [[nodiscard]] QPointF getWidgetPosition() const;

private:
  [[nodiscard]] QSizeF calculateLabelSize() const;
  [[nodiscard]] QSizeF calculateWidgetSize() const;
  [[nodiscard]] QSizeF calculatePinsSize() const;
  [[nodiscard]] float calculatePinsWidth(flow::node::Pin::Type type) const;

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

#endif//PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H
