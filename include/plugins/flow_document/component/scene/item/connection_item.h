#ifndef FLOW_DOCUMENT_CONNECTION_ITEM_H
#define FLOW_DOCUMENT_CONNECTION_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Connection;

class FLOW_DOCUMENT_API ConnectionItem : public ObjectItem {
  Q_OBJECT

 public:
  explicit ConnectionItem(Connection* flow, FlowDocument* document,
                          QGraphicsItem* parent = nullptr);
  ~ConnectionItem() override;

  [[nodiscard]] Connection* getConnection() const;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_ITEM_H
