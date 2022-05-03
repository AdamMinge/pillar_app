#ifndef FLOW_SELECTION_RACTANGLE_H
#define FLOW_SELECTION_RACTANGLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API SelectionRectangle : public QGraphicsItem
{
public:
  explicit SelectionRectangle(QGraphicsItem *parent = nullptr);
  ~SelectionRectangle() override;

  void setRect(const QRectF &rect);
  [[nodiscard]] QRectF boundingRect() const override;

  void paint(
    QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget) override;

private:
  QRectF m_rect;
};

#endif//FLOW_SELECTION_RACTANGLE_H
