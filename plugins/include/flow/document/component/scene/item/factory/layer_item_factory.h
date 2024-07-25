#ifndef FLOW_DOCUMENT_LAYER_ITEM_FACTORY_H
#define FLOW_DOCUMENT_LAYER_ITEM_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/factory/item_factory.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------------- GroupLayerItemFactory ----------------------- */

class LIB_FLOW_DOCUMENT_API GroupLayerItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ItemFactory)

 public:
  explicit GroupLayerItemFactory(QObject* parent = nullptr);
  ~GroupLayerItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

/* ---------------------------- NodeLayerItemFactory ------------------------ */

class LIB_FLOW_DOCUMENT_API NodeLayerItemFactory : public ItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ItemFactory)

 public:
  explicit NodeLayerItemFactory(QObject* parent = nullptr);
  ~NodeLayerItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_LAYER_ITEM_FACTORY_H
