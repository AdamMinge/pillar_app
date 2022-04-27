/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_table_model.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/action_manager.h>
/* -------------------------------------------------------------------------- */

ShortcutsTableModel::ShortcutsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
  connect(
    &flow::ActionManager::getInstance(), &flow::ActionManager::registeredAction,
    this, &ShortcutsTableModel::addedShortcut);

  connect(
    &flow::ActionManager::getInstance(),
    &flow::ActionManager::unregisteredAction, this,
    &ShortcutsTableModel::removedShortcut);

  init();
}

ShortcutsTableModel::~ShortcutsTableModel() = default;

bool ShortcutsTableModel::apply()
{
  std::for_each(m_actions.begin(), m_actions.end(), [](auto &shortcut_data) {
    flow::ActionManager::getInstance().setCustomShortcut(
      shortcut_data.action_id, shortcut_data.key_sequence);
  });

  return applied();
}

bool ShortcutsTableModel::applied() const
{
  return std::all_of(
    m_actions.begin(), m_actions.end(), [](auto &shortcut_data) {
      return shortcut_data.action->shortcut() == shortcut_data.key_sequence;
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
    auto shortcut_data = m_actions.at(index.row());
    switch (index.column())
    {
      case Column::ActionColumn:
        return shortcut_data.action->whatsThis();

      case Column::ShortcutColumn:
        return shortcut_data.key_sequence;

      case Column::ActionIdColumn:
        return shortcut_data.action_id;

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

  if (role == Qt::DisplayRole && index.column() == Column::ShortcutColumn)
  {
    auto applied_before = applied();
    m_actions.at(index.row()).key_sequence = value.value<QKeySequence>();
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
      case Column::ActionColumn:
        return tr("Action");

      case Column::ShortcutColumn:
        return tr("Shortcut");

      case Column::ActionIdColumn:
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
  if (index.column() == Column::ShortcutColumn) flags |= Qt::ItemIsEditable;

  return flags;
}

void ShortcutsTableModel::init()
{
  const auto actions = flow::ActionManager::getInstance().getActionsId();
  for (const auto &action : actions)
  {
    auto found_action = flow::ActionManager::getInstance().findAction(action);
    Q_ASSERT(found_action);

    m_actions.emplace_back(
      ShortcutData{found_action, action, found_action->shortcut()});
  }
}

void ShortcutsTableModel::addedShortcut(const QString &action_id)
{
  auto shortcut_data_iter = std::find_if(
    m_actions.begin(), m_actions.end(), [&action_id](auto &shortcut_data) {
      return shortcut_data.action_id == action_id;
    });

  if (shortcut_data_iter == m_actions.end())
  {
    auto row = m_actions.size();
    auto action = flow::ActionManager::getInstance().findAction(action_id);

    beginInsertRows(QModelIndex{}, row, row);
    m_actions.push_back(ShortcutData{action, action_id, action->shortcut()});
    endInsertRows();
  }
}

void ShortcutsTableModel::removedShortcut(const QString &action_id)
{
  auto shortcut_data_iter = std::find_if(
    m_actions.begin(), m_actions.end(), [&action_id](auto &shortcut_data) {
      return shortcut_data.action_id == action_id;
    });

  if (shortcut_data_iter != m_actions.end())
  {
    auto row = std::distance(m_actions.begin(), shortcut_data_iter);

    beginRemoveRows(QModelIndex{}, row, row);
    m_actions.erase(shortcut_data_iter);
    endRemoveRows();
  }
}
