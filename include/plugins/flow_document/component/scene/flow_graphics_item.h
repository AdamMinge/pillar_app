#ifndef FLOW_DOCUMENT_FLOW_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_FLOW_GRAPHICS_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowObject;
class FlowDocument;
class ChangeEvent;

class FLOW_DOCUMENT_API FlowGraphicsItem : public QGraphicsObject {
  Q_OBJECT

 public:
  explicit FlowGraphicsItem(FlowDocument *document, FlowObject *object,
                            QGraphicsItem *parent = nullptr);
  ~FlowGraphicsItem() override;

  [[nodiscard]] FlowObject *getObject() const;
  [[nodiscard]] FlowDocument *getDocument() const;

  void setHovered(bool hovered);
  [[nodiscard]] bool isHovered() const;

 private Q_SLOTS:
  void onEvent(const ChangeEvent &event);

 private:
  FlowDocument *m_document;
  FlowObject *m_object;
  bool m_hovered;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_GRAPHICS_ITEM_H
