/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_table_delegate.h"
#include "flow/editor/settings/shortcuts_table_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/action_manager.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/widget/shortcut_selector.h>
/* -------------------------------------------------------------------------- */

ShortcutsTableDelegate::ShortcutsTableDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

ShortcutsTableDelegate::~ShortcutsTableDelegate() = default;

void ShortcutsTableDelegate::paint(
  QPainter *painter, const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{
  QStyledItemDelegate::paint(painter, option, index);

  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  const auto model = index.model();
  const auto shortcut_valid_index =
    model->index(index.row(), ShortcutsTableModel::Column::ValidColumn);
  const auto shortcut_applied_index =
    model->index(index.row(), ShortcutsTableModel::Column::AppliedColumn);

  const auto shortcut_valid =
    model->data(shortcut_valid_index, Qt::DisplayRole).toBool();
  const auto shortcut_applied =
    model->data(shortcut_applied_index, Qt::DisplayRole).toBool();

  if (!shortcut_valid || !shortcut_applied)
  {
    painter->save();
    painter->setPen(
      !shortcut_valid ? Qt::GlobalColor::red : Qt::GlobalColor::green);

    painter->drawRect(opt.rect.adjusted(0, 0, -1, -1));
    painter->restore();
  }
}

QWidget *ShortcutsTableDelegate::createEditor(
  QWidget *parent, const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{
  if (index.column() != ShortcutsTableModel::Column::ShortcutColumn)
    return QStyledItemDelegate::createEditor(parent, option, index);

  return new utils::ShortcutSelector(parent);
}

void ShortcutsTableDelegate::setEditorData(
  QWidget *editor, const QModelIndex &index) const
{
  if (index.column() != ShortcutsTableModel::Column::ShortcutColumn)
    return QStyledItemDelegate::setEditorData(editor, index);

  auto shortcut_selector = qobject_cast<utils::ShortcutSelector *>(editor);
  shortcut_selector->setText(index.data(Qt::DisplayRole).toString());
}

void ShortcutsTableDelegate::setModelData(
  QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if (index.column() != ShortcutsTableModel::Column::ShortcutColumn)
    return QStyledItemDelegate::setModelData(editor, model, index);

  auto shortcut_selector = qobject_cast<utils::ShortcutSelector *>(editor);
  auto key_sequence = QKeySequence(shortcut_selector->text());
  model->setData(index, key_sequence, Qt::DisplayRole);
}
