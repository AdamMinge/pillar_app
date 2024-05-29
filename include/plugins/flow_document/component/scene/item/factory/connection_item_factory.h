#ifndef FLOW_DOCUMENT_CONNECTION_ITEM_FACTORY_H
#define FLOW_DOCUMENT_CONNECTION_ITEM_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/item_factory.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- ConnectionItemFactory ----------------------- */

class FLOW_DOCUMENT_API ConnectionItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ItemFactory)

 public:
  explicit ConnectionItemFactory(QObject* parent = nullptr);
  ~ConnectionItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_ITEM_FACTORY_H
