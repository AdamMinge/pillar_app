#ifndef FLOW_DOCUMENT_SELECTION_RECTANGLE_H
#define FLOW_DOCUMENT_SELECTION_RECTANGLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API SelectionRectangle : public QGraphicsItem {
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

}  // namespace flow

#endif  // FLOW_DOCUMENT_SELECTION_RECTANGLE_H
