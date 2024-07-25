#ifndef FLOW_DOCUMENT_FLOW_ITEM_H
#define FLOW_DOCUMENT_FLOW_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/object_item.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Flow;
class LayerItem;

class LIB_FLOW_DOCUMENT_API FlowItem : public ObjectItem {
  Q_OBJECT

 public:
  explicit FlowItem(Flow* flow, FlowDocument* document,
                    QGraphicsItem* parent = nullptr);
  ~FlowItem() override;

  [[nodiscard]] Flow* getFlow() const;

 private:
  LayerItem* m_root_item;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_ITEM_H
