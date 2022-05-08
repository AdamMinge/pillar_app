#ifndef PLUGIN_FLOW_FLOW_ITEM_H
#define PLUGIN_FLOW_FLOW_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{
  class Object;
}

class FLOW_DOCUMENT_API FlowItem : public QGraphicsObject
{
  Q_OBJECT

public:
  explicit FlowItem(flow::Object *object, QGraphicsItem *parent = nullptr);
  ~FlowItem() override;

  [[nodiscard]] flow::Object *getObject() const;

  void setHovered(bool hovered);
  [[nodiscard]] bool isHovered() const;

private:
  flow::Object *m_object;
  bool m_hovered;
};

#endif//PLUGIN_FLOW_FLOW_ITEM_H
