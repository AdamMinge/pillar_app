/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_table_model.h"
#include "flow/editor/action_manager.h"
/* -------------------------------------------------------------------------- */

ShortcutsTableModel::ShortcutsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
  const auto actions = ActionManager::getInstance().getActionsId();
  for (const auto &action : actions)
  {
    auto found_action = ActionManager::getInstance().findAction(action);
    Q_ASSERT(found_action);

    m_actions.emplace_back(
      std::make_pair(found_action, found_action->shortcut()));
  }
}

ShortcutsTableModel::~ShortcutsTableModel() = default;

bool ShortcutsTableModel::apply()
{
  std::for_each(m_actions.begin(), m_actions.end(), [](auto &action_pair) {
    auto action_id =
      ActionManager::getInstance().getActionId(action_pair.first);
    ActionManager::getInstance().setCustomShortcut(
      action_id, action_pair.second);
  });

  return applied();
}

bool ShortcutsTableModel::applied() const
{
  return std::all_of(m_actions.begin(), m_actions.end(), [](auto &action_pair) {
    return action_pair.first->shortcut() == action_pair.second;
  });
}

int ShortcutsTableModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(m_actions.size());
}

int ShortcutsTableModel::columnCount(const QModelIndex &parent) const
{
  return 3;
}

QVariant ShortcutsTableModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  if (role == Qt::DisplayRole)
  {
    auto action_pair = m_actions.at(index.row());
    switch (index.column())
    {
      case Column::Action:
        return action_pair.first->whatsThis();

      case Column::Shortcut:
        return action_pair.second;

      case Column::ActionId:
        return ActionManager::getInstance().getActionId(action_pair.first);

      default:
        return QVariant{};
    }
  }

  return QVariant{};
}

bool ShortcutsTableModel::setData(
  const QModelIndex &index, const QVariant &value, int role)
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent())) return false;

  if (role == Qt::DisplayRole && index.column() == Column::Shortcut)
  {
    auto applied_before = applied();
    m_actions.at(index.row()).second = value.value<QKeySequence>();
    auto applied_after = applied();

    if (applied_before != applied_after) Q_EMIT appliedChanged(applied_after);
    return true;
  }

  return false;
}

QVariant ShortcutsTableModel::headerData(
  int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
    switch (section)
    {
      case Column::Action:
        return tr("Action");

      case Column::Shortcut:
        return tr("Shortcut");

      case Column::ActionId:
        return tr("Action Id");

      default:
        return QVariant{};
    }
  }
  return QVariant{};
}

Qt::ItemFlags ShortcutsTableModel::flags(const QModelIndex &index) const
{
  auto flags = QAbstractTableModel::flags(index);
  if (index.column() == Column::Shortcut) flags |= Qt::ItemIsEditable;

  return flags;
}
