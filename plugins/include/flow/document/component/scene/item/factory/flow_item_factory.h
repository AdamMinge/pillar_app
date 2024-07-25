#ifndef FLOW_DOCUMENT_FLOW_ITEM_FACTORY_H
#define FLOW_DOCUMENT_FLOW_ITEM_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/factory/item_factory.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------- FlowItemFactory -------------------------- */

class LIB_FLOW_DOCUMENT_API FlowItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ItemFactory)

 public:
  explicit FlowItemFactory(QObject* parent = nullptr);
  ~FlowItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_ITEM_FACTORY_H
