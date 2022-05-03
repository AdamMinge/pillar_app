#ifndef FLOW_TYPE_CONVERTERS_TREE_DELEGATE_H
#define FLOW_TYPE_CONVERTERS_TREE_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowTypeConvertersTreeDelegate
    : public QStyledItemDelegate
{
  Q_OBJECT

public:
  explicit FlowTypeConvertersTreeDelegate(QObject *parent = nullptr);
  ~FlowTypeConvertersTreeDelegate() override;

  void paint(
    QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;

private:
  const QSize m_icon_size;
  const int m_spacing;
};

#endif//FLOW_TYPE_CONVERTERS_TREE_DELEGATE_H
