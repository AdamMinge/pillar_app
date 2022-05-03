#ifndef PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H
#define PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/node/pin.h"
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowNodeItem;

class FLOW_DOCUMENT_API FlowNodeGeometry
{
public:
  explicit FlowNodeGeometry(const FlowNodeItem &node_item);
  virtual ~FlowNodeGeometry();

  void recalculate();

  [[nodiscard]] QRectF getBoundingRect() const;
  [[nodiscard]] QPointF
  getPinPosition(flow::node::Pin::Type type, int index) const;
  [[nodiscard]] QPointF getWidgetPosition() const;

private:
  [[nodiscard]] QSizeF getLabelSize() const;
  [[nodiscard]] QSizeF getWidgetSize() const;
  [[nodiscard]] QSizeF getPinsSize() const;

  [[nodiscard]] float getPinsWidth(flow::node::Pin::Type type) const;

private:
  const FlowNodeItem &m_node_item;
  QSizeF m_size;
  QSizeF m_spacing;
};

#endif//PLUGIN_FLOW_FLOW_NODE_GEOMETRY_H
