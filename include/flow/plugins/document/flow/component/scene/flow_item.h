#ifndef PLUGIN_FLOW_FLOW_ITEM_H
#define PLUGIN_FLOW_FLOW_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowItem : public QGraphicsObject
{
  Q_OBJECT

public:
  explicit FlowItem(QGraphicsItem *parent = nullptr);
  ~FlowItem() override;

  void setHovered(bool hovered);
  [[nodiscard]] bool isHovered() const;

private:
  bool m_hovered;
};

#endif//PLUGIN_FLOW_FLOW_ITEM_H
