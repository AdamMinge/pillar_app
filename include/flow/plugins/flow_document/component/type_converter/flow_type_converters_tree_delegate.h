#ifndef FLOW_TYPE_CONVERTERS_TREE_DELEGATE_H
#define FLOW_TYPE_CONVERTERS_TREE_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class FLOW_DOCUMENT_API FlowTypeConvertersTreeDelegate
    : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit FlowTypeConvertersTreeDelegate(QObject *parent = nullptr);
  ~FlowTypeConvertersTreeDelegate() override;

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override;

 private:
  const QSize m_icon_size;
  const int m_spacing;
};

}  // namespace plugin::flow_document

#endif  // FLOW_TYPE_CONVERTERS_TREE_DELEGATE_H
