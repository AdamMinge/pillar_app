#ifndef FLOW_DOCUMENT_CUBIC_PATH_ITEM_H
#define FLOW_DOCUMENT_CUBIC_PATH_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
#include <QPainterPath>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- CubicPathItem -------------------------- */

class FLOW_DOCUMENT_API CubicPathItem : public QGraphicsItem {
  using PointsPair = std::pair<QPointF, QPointF>;

 public:
  explicit CubicPathItem(QGraphicsItem* parent = nullptr);
  ~CubicPathItem() override;

  void setStartPos(QPointF start);
  [[nodiscard]] QPointF getStartPos() const;

  void setEndPos(QPointF end);
  [[nodiscard]] QPointF getEndPos() const;

  [[nodiscard]] QRectF boundingRect() const override;
  [[nodiscard]] QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 private:
  PointsPair calculateControlPoints(const QPointF& start,
                                    const QPointF& end) const;

 private:
  QPainterPath m_path;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CUBIC_PATH_ITEM_H
