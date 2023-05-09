#ifndef FLOW_DOCUMENT_OBJECT_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_OBJECT_GRAPHICS_ITEM_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Object;
class FlowDocument;
class ChangeEvent;

class FLOW_DOCUMENT_API ObjectGraphicsItem : public GraphicsItem {
  Q_OBJECT

 public:
  explicit ObjectGraphicsItem(FlowDocument *document, Object *object,
                              QGraphicsItem *parent);
  ~ObjectGraphicsItem() override;

  [[nodiscard]] Object *getObject() const;
  [[nodiscard]] FlowDocument *getDocument() const;

 private:
  void onEvent(const ChangeEvent &event);

 private:
  FlowDocument *m_document;
  Object *m_object;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_GRAPHICS_ITEM_H
