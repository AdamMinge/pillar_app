/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_table_model.h"
#include "flow/editor/action_manager.h"
/* -------------------------------------------------------------------------- */

ShortcutsTableModel::ShortcutsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
  const auto actions = ActionManager::getInstance().getActions();
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
  std::for_each(m_actions.begin(), m_actions.end(), [](auto &plugin_pair) {
    plugin_pair.first->setShortcut(plugin_pair.second);
  });

  return applied();
}

bool ShortcutsTableModel::applied() const
{
  return std::all_of(m_actions.begin(), m_actions.end(), [](auto &plugin_pair) {
    return plugin_pair.first->shortcut() == plugin_pair.second;
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
      case 0:
        return action_pair.first->whatsThis();
      case 1:
        return action_pair.second;
      case 2:
        return ActionManager::getInstance().getActionId(action_pair.first);
      default:
        break;
    }
  }

  return QVariant{};
}

bool ShortcutsTableModel::setData(
  const QModelIndex &index, const QVariant &value, int role)
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent())) return false;

  if (role == Qt::DisplayRole && index.column() == 1)
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
      case 0:
        return tr("Action");
      case 1:
        return tr("Shortcut");
      case 2:
        return tr("Action Id");
      default:
        break;
    }
  }
  return QVariant{};
}

Qt::ItemFlags ShortcutsTableModel::flags(const QModelIndex &index) const
{
  auto flags = QAbstractTableModel::flags(index);
  if (index.column() == 1) flags |= Qt::ItemIsEditable;

  return flags;
}
