#ifndef FLOW_PLUGIN_LIST_DELEGATE_H
#define FLOW_PLUGIN_LIST_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* -------------------------------------------------------------------------- */

class PluginListDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit PluginListDelegate(QObject *parent = nullptr);
  ~PluginListDelegate() override;

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override;

 private:
  const QSize m_icon_size;
  const QMargins m_margins;
  const int m_spacing;
};

#endif  // FLOW_PLUGIN_LIST_DELEGATE_H
