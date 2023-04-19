#ifndef PLUGIN_FLOW_FLOW_ITEM_H
#define PLUGIN_FLOW_FLOW_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class Object;
class FlowDocument;
class ObjectsChangedPropertiesEvent;

class FLOW_DOCUMENT_API FlowItem : public QGraphicsObject {
  Q_OBJECT

 public:
  explicit FlowItem(FlowDocument *document, Object *object,
                    QGraphicsItem *parent = nullptr);
  ~FlowItem() override;

  [[nodiscard]] Object *getObject() const;
  [[nodiscard]] FlowDocument *getDocument() const;

  void setHovered(bool hovered);
  [[nodiscard]] bool isHovered() const;

 private Q_SLOTS:
  void onEvent(const ObjectsChangedPropertiesEvent &event);

 private:
  FlowDocument *m_document;
  Object *m_object;
  bool m_hovered;
};

}  // namespace plugin::flow_document

#endif  // PLUGIN_FLOW_FLOW_ITEM_H
