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

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GRAPHICS_ITEM_FACTORY_H
