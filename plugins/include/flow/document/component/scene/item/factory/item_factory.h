#ifndef FLOW_DOCUMENT_ITEM_FACTORY_H
#define FLOW_DOCUMENT_ITEM_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class ObjectItem;
class FlowDocument;
class Object;

/* -------------------------------- ItemFactory ----------------------------- */

class LIB_FLOW_DOCUMENT_API ItemFactory : public QObject {
  Q_OBJECT

 public:
  explicit ItemFactory(QObject* parent = nullptr);
  ~ItemFactory() override;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
  [[nodiscard]] virtual ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const = 0;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::ItemFactory, "org.flow.ItemFactory")

#endif  // FLOW_DOCUMENT_ITEM_FACTORY_H