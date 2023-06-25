#ifndef FLOW_DOCUMENT_GRAPHICS_ITEM_FACTORY_H
#define FLOW_DOCUMENT_GRAPHICS_ITEM_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GraphicsItem;
class FlowDocument;
class Object;

/* ---------------------------- GraphicsItemFactory ------------------------- */

class FLOW_DOCUMENT_API GraphicsItemFactory : public QObject {
  Q_OBJECT

 public:
  explicit GraphicsItemFactory(QObject* parent = nullptr);
  ~GraphicsItemFactory() override;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
  [[nodiscard]] virtual GraphicsItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::GraphicsItemFactory,
                    "org.flow.GraphicsItemFactory")

namespace flow_document {

/* ------------------------------- FlowItemFactory -------------------------- */

class FLOW_DOCUMENT_API FlowItemFactory : public GraphicsItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::GraphicsItemFactory)

 public:
  explicit FlowItemFactory(QObject* parent = nullptr);
  ~FlowItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] GraphicsItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

/* ---------------------------- GroupLayerItemFactory ----------------------- */

class FLOW_DOCUMENT_API GroupLayerItemFactory : public GraphicsItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::GraphicsItemFactory)

 public:
  explicit GroupLayerItemFactory(QObject* parent = nullptr);
  ~GroupLayerItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] GraphicsItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

/* ---------------------------- NodeLayerItemFactory ------------------------ */

class FLOW_DOCUMENT_API NodeLayerItemFactory : public GraphicsItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::GraphicsItemFactory)

 public:
  explicit NodeLayerItemFactory(QObject* parent = nullptr);
  ~NodeLayerItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] GraphicsItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

/* ------------------------------- NodeItemFactory -------------------------- */

class FLOW_DOCUMENT_API NodeItemFactory : public GraphicsItemFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::GraphicsItemFactory)

 public:
  explicit NodeItemFactory(QObject* parent = nullptr);
  ~NodeItemFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] GraphicsItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const override;
};

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] GraphicsItem* createGraphicsItem(Object* object,
                                               FlowDocument* document,
                                               QGraphicsItem* parent = nullptr);

[[nodiscard]] GraphicsItemFactory* getGraphicsItemFactoryByObject(
    Object* object);

template <typename GRAPHICS_ITEM>
[[nodiscard]] GRAPHICS_ITEM* createGraphicsItem(
    Object* object, FlowDocument* document, QGraphicsItem* parent = nullptr) {
  auto item = createGraphicsItem(object, document, parent);
  auto casted_item = qobject_cast<GRAPHICS_ITEM*>(item);
  Q_ASSERT(casted_item);

  return casted_item;
}

}  // namespace flow_document

/* ----------------------- Helper macro to create factory ------------------- */

#define DECLARE_GRAPHICS_ITEM_FACTORY(EXPORT_API, ITEM, OBJECT)                \
  class EXPORT_API ITEM##Factory : public flow_document::GraphicsItemFactory { \
    Q_OBJECT                                                                   \
    Q_INTERFACES(flow_document::GraphicsItemFactory)                           \
   public:                                                                     \
    explicit ITEM##Factory(QObject* parent = nullptr)                          \
        : flow_document::GraphicsItemFactory(parent) {}                        \
                                                                               \
    [[nodiscard]] QString getObjectClassName() const override {                \
      return OBJECT::sGetClassName();                                          \
    }                                                                          \
    [[nodiscard]] flow_document::GraphicsItem* create(                         \
        flow_document::Object* object, flow_document::FlowDocument* document,  \
        QGraphicsItem* parent = nullptr) const override {                      \
      return new ITEM(static_cast<OBJECT*>(object), document, parent);         \
    }                                                                          \
  };

#endif  // FLOW_DOCUMENT_GRAPHICS_ITEM_FACTORY_H
