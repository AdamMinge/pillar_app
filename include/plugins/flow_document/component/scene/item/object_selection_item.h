#ifndef FLOW_DOCUMENT_OBJECT_SELECTION_ITEM_H
#define FLOW_DOCUMENT_OBJECT_SELECTION_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- ObjectOutlineItem -------------------------- */

class FLOW_DOCUMENT_API ObjectOutlineItem : public QGraphicsItem {
 public:
  enum class Role { Hover, Selection };

 public:
  explicit ObjectOutlineItem(Role role, QGraphicsItem *parent = nullptr);
  ~ObjectOutlineItem() override;

  [[nodiscard]] QRectF boundingRect() const override;
  [[nodiscard]] QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
};

/* ---------------------------- ObjectSelectionItem ------------------------- */

class FLOW_DOCUMENT_API ObjectSelectionItem : public QGraphicsItem {
 public:
  explicit ObjectSelectionItem(QGraphicsItem *parent = nullptr);
  ~ObjectSelectionItem() override;

  [[nodiscard]] QRectF boundingRect() const override;
  [[nodiscard]] QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private:
  ObjectOutlineItem *m_hover;
  ObjectOutlineItem *m_selection;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_SELECTION_ITEM_H
