#ifndef FLOW_DOCUMENT_NODE_ITEM_FACTORY_H
#define FLOW_DOCUMENT_NODE_ITEM_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/factory/item_factory.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------- NodeItemFactory -------------------------- */

class LIB_FLOW_DOCUMENT_API NodeItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ItemFactory)

 public:
  explicit NodeItemFactory(QObject* parent = nullptr);
  ~NodeItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODE_ITEM_FACTORY_H
