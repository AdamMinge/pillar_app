#ifndef FLOW_SHORTCUTS_TABLE_DELEGATE_H
#define FLOW_SHORTCUTS_TABLE_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QStyledItemDelegate>
/* -------------------------------------------------------------------------- */

class ShortcutsTableDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  explicit ShortcutsTableDelegate(QObject *parent = nullptr);
  ~ShortcutsTableDelegate() override;

  [[nodiscard]] QWidget *createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(
    QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const override;
  bool editorEvent(
    QEvent *event, QAbstractItemModel *model,
    const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif//FLOW_SHORTCUTS_TABLE_DELEGATE_H
