#ifndef FLOW_DOCUMENT_ITEM_FACTORY_UTILS_H
#define FLOW_DOCUMENT_ITEM_FACTORY_UTILS_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/item_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Qtils -------------------------------- */

[[nodiscard]] ObjectItem* createItem(Object* object, FlowDocument* document,
                                     QGraphicsItem* parent = nullptr);

[[nodiscard]] ItemFactory* getItemFactoryByObject(Object* object);

template <typename GRAPHICS_ITEM>
[[nodiscard]] GRAPHICS_ITEM* createItem(Object* object, FlowDocument* document,
                                        QGraphicsItem* parent = nullptr) {
  auto item = createItem(object, document, parent);
  auto casted_item = qobject_cast<GRAPHICS_ITEM*>(item);
  Q_ASSERT(casted_item);

  return casted_item;
}

}  // namespace flow_document

/* ----------------------- Helper macro to create factory ------------------- */

#define DECLARE_GRAPHICS_ITEM_FACTORY(EXPORT_API, ITEM, OBJECT)               \
  class EXPORT_API ITEM##Factory : public flow_document::ItemFactory {        \
    Q_OBJECT                                                                  \
    Q_INTERFACES(flow_document::ItemFactory)                                  \
   public:                                                                    \
    explicit ITEM##Factory(QObject* parent = nullptr)                         \
        : flow_document::ItemFactory(parent) {}                               \
                                                                              \
    [[nodiscard]] QString getObjectClassName() const override {               \
      return OBJECT::sGetClassName();                                         \
    }                                                                         \
    [[nodiscard]] flow_document::ObjectItem* create(                          \
        flow_document::Object* object, flow_document::FlowDocument* document, \
        QGraphicsItem* parent = nullptr) const override {                     \
      return new ITEM(static_cast<OBJECT*>(object), document, parent);        \
    }                                                                         \
  };

#endif  // FLOW_DOCUMENT_ITEM_FACTORY_UTILS_H
