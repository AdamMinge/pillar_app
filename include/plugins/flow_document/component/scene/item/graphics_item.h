#ifndef FLOW_DOCUMENT_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_GRAPHICS_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API GraphicsItem : public QGraphicsObject {
  Q_OBJECT

 public:
  explicit GraphicsItem(QGraphicsItem *parent = nullptr);
  ~GraphicsItem() override;

  void setHovered(bool hovered);
  [[nodiscard]] bool isHovered() const;

 private:
  bool m_hovered;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GRAPHICS_ITEM_H
