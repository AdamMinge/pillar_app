#ifndef FLOW_DOCUMENT_ITEM_FACTORY_H
#define FLOW_DOCUMENT_ITEM_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ObjectItem;
class FlowDocument;
class Object;

/* -------------------------------- ItemFactory ----------------------------- */

class FLOW_DOCUMENT_API ItemFactory : public QObject {
  Q_OBJECT

 public:
  explicit ItemFactory(QObject* parent = nullptr);
  ~ItemFactory() override;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
  [[nodiscard]] virtual ObjectItem* create(
      Object* object, FlowDocument* document,
      QGraphicsItem* parent = nullptr) const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ItemFactory, "org.flow.ItemFactory")

#endif  // FLOW_DOCUMENT_ITEM_FACTORY_H