#ifndef FLOW_SELECTION_RACTANGLE_H
#define FLOW_SELECTION_RACTANGLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API SelectionRectangle : public QGraphicsItem {
 public:
  explicit SelectionRectangle(QGraphicsItem *parent = nullptr);
  ~SelectionRectangle() override;

  void setRect(const QRectF &rect);
  [[nodiscard]] QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private:
  QRectF m_rect;
};

}  // namespace flow_document

#endif  // FLOW_SELECTION_RACTANGLE_H
