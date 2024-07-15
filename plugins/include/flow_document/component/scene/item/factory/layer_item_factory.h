#ifndef FLOW_DOCUMENT_LAYER_ITEM_FACTORY_H
#define FLOW_DOCUMENT_LAYER_ITEM_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/item_factory.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- GroupLayerItemFactory ----------------------- */

class FLOW_DOCUMENT_API GroupLayerItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ItemFactory)

 public:
  explicit GroupLayerItemFactory(QObject* parent = nullptr);
  ~GroupLayerItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

/* ---------------------------- NodeLayerItemFactory ------------------------ */

class FLOW_DOCUMENT_API NodeLayerItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ItemFactory)

 public:
  explicit NodeLayerItemFactory(QObject* parent = nullptr);
  ~NodeLayerItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_ITEM_FACTORY_H
