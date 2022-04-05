/* ------------------------------------ Qt ---------------------------------- */
#include <QMenu>
#include <QMouseEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/action_manager.h"
#include "flow/editor/settings/shortcuts_table_delegate.h"
#include "flow/editor/settings/shortcuts_table_model.h"
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/widget/shortcut_selector.h>
/* -------------------------------------------------------------------------- */

ShortcutsTableDelegate::ShortcutsTableDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

ShortcutsTableDelegate::~ShortcutsTableDelegate() = default;

QWidget *ShortcutsTableDelegate::createEditor(
  QWidget *parent, const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{
  return new utils::ShortcutSelector(parent);
}

void ShortcutsTableDelegate::setEditorData(
  QWidget *editor, const QModelIndex &index) const
{
  auto shortcut_selector = qobject_cast<utils::ShortcutSelector *>(editor);
  shortcut_selector->setText(index.data(Qt::DisplayRole).toString());
}

void ShortcutsTableDelegate::setModelData(
  QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  auto shortcut_selector = qobject_cast<utils::ShortcutSelector *>(editor);
  auto key_sequence = QKeySequence(shortcut_selector->text());
  model->setData(index, key_sequence, Qt::DisplayRole);
}

bool ShortcutsTableDelegate::editorEvent(
  QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
  const QModelIndex &index)
{
  if (event->type() == QEvent::MouseButtonPress)
  {
    auto mouse_event = dynamic_cast<QMouseEvent *>(event);
    Q_ASSERT(mouse_event);

    if (mouse_event->button() == Qt::MouseButton::RightButton)
    {
      auto menu = new QMenu;
      menu->setAttribute(Qt::WA_DeleteOnClose);
      menu->addAction(tr("Set to Default"), [index, model]() {
        const auto action_id_index = model->index(index.row(), 2);
        const auto action_shortcut_index = model->index(index.row(), 1);

        const auto action_id =
          model->data(action_id_index, Qt::DisplayRole).toString();
        const auto action_default_shortcut =
          ActionManager::getInstance().getDefaultShortcut(action_id);

        model->setData(
          action_shortcut_index, action_default_shortcut, Qt::DisplayRole);
      });
      menu->addAction(tr("Clear"), [index, model]() {
        model->setData(index, QVariant{}, Qt::DisplayRole);
      });

      menu->popup(mouse_event->globalPosition().toPoint());
    }
  }

  return QStyledItemDelegate::editorEvent(event, model, option, index);
}
