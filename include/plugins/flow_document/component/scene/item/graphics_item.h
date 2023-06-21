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

 protected:
  template <typename GRAPHICS_ITEM>
  [[nodiscard]] static GRAPHICS_ITEM* creatItem(Object* object,
                                                FlowDocument* document,
                                                QGraphicsItem* parent);
  [[nodiscard]] static GraphicsItem* creatItem(Object* object,
                                               FlowDocument* document,
                                               QGraphicsItem* parent);
  [[nodiscard]] static GraphicsItemFactory* getFactoryByObject(Object* object);

 private:
  Object* m_object;
  FlowDocument* m_document;
  bool m_hovered;
};

template <typename GRAPHICS_ITEM>
[[nodiscard]] GRAPHICS_ITEM* GraphicsItem::creatItem(Object* object,
                                                     FlowDocument* document,
                                                     QGraphicsItem* parent) {
  auto item = creatItem(object, document, parent);
  auto casted_item = qobject_cast<GRAPHICS_ITEM*>(item);
  Q_ASSERT(casted_item);

  return casted_item;
}

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GRAPHICS_ITEM_H
