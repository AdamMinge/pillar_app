#ifndef FLOW_DOCUMENT_OBJECT_SELECTION_ITEM_H
#define FLOW_DOCUMENT_OBJECT_SELECTION_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsItem>
#include <QTimer>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Node;

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

 private:
  QTimer m_timer;
  qreal m_dash_offset;
};

/* ---------------------------- ObjectSelectionItem ------------------------- */

class FLOW_DOCUMENT_API ObjectSelectionItem : public QGraphicsItem {
 public:
  explicit ObjectSelectionItem(QGraphicsItem *parent = nullptr);
  ~ObjectSelectionItem() override;

  void setHovered(bool hovered);
  void setSelected(bool selected);

  [[nodiscard]] bool isHovered() const;
  [[nodiscard]] bool isSelected() const;

  [[nodiscard]] QRectF boundingRect() const override;
  [[nodiscard]] QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private:
  ObjectOutlineItem *m_hover;
  ObjectOutlineItem *m_selection;
};

/* ----------------------------- NodeSelectionItem -------------------------- */

class FLOW_DOCUMENT_API NodeSelectionItem : public QObject,
                                            public ObjectSelectionItem {
  Q_OBJECT

 public:
  explicit NodeSelectionItem(Node *node, FlowDocument *document,
                             QGraphicsItem *parent = nullptr);
  ~NodeSelectionItem() override;

 private:
  Node *m_node;
  FlowDocument *m_document;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_SELECTION_ITEM_H
