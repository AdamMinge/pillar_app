#ifndef FLOW_DOCUMENT_OBJECT_ITEM_H
#define FLOW_DOCUMENT_OBJECT_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Object;
class ChangeEvent;
class FlowDocument;

class LIB_FLOW_DOCUMENT_API ObjectItem : public QGraphicsObject {
  Q_OBJECT

 public:
  explicit ObjectItem(Object* object, FlowDocument* document,
                      QGraphicsItem* parent = nullptr);
  ~ObjectItem() override;

  virtual void init();

  [[nodiscard]] Object* getObject() const;
  [[nodiscard]] FlowDocument* getDocument() const;

  [[nodiscard]] QRectF boundingRect() const override;
  void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

 protected Q_SLOTS:
  [[nodiscard]] QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant& value) override;

  virtual void onEvent(const ChangeEvent& event);
  virtual void onSceneChanged();

 private:
  Object* m_object;
  FlowDocument* m_document;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_OBJECT_ITEM_H
