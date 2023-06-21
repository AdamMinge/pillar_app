#ifndef FLOW_DOCUMENT_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_GRAPHICS_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Object;
class ChangeEvent;
class FlowDocument;

class GraphicsItemFactory;

class FLOW_DOCUMENT_API GraphicsItem : public QGraphicsObject {
  Q_OBJECT

 public:
  explicit GraphicsItem(Object* object, FlowDocument* document,
                        QGraphicsItem* parent = nullptr);
  ~GraphicsItem() override;

  void setHovered(bool hovered);
  [[nodiscard]] bool isHovered() const;

  [[nodiscard]] Object* getObject() const;
  [[nodiscard]] FlowDocument* getDocument() const;

  QRectF boundingRect() const override;
  void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

 protected Q_SLOTS:
  virtual void onEvent(const ChangeEvent& event);

 private:
  Object* m_object;
  FlowDocument* m_document;
  bool m_hovered;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GRAPHICS_ITEM_H
