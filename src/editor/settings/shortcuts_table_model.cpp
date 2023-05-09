/* ----------------------------------- Local -------------------------------- */
#include "settings/shortcuts_table_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMultiMap>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/action_manager.h>
/* -------------------------------------------------------------------------- */

ShortcutsTableModel::ShortcutsTableModel(QObject *parent)
    : QAbstractTableModel(parent) {
  connect(&egnite::ActionManager::getInstance(),
          &egnite::ActionManager::registeredAction, this,
          &ShortcutsTableModel::addedShortcut);

  connect(&egnite::ActionManager::getInstance(),
          &egnite::ActionManager::unregisteredAction, this,
          &ShortcutsTableModel::removedShortcut);

  init();
}

ShortcutsTableModel::~ShortcutsTableModel() = default;

bool ShortcutsTableModel::apply() {
  for (auto i = 0; i < m_actions.size(); ++i) {
    const auto &shortcut_data = m_actions[i];
    if (shortcut_data.action->shortcut() != shortcut_data.key_sequence) {
      egnite::ActionManager::getInstance().setCustomShortcut(
          shortcut_data.action_id, shortcut_data.key_sequence);

      Q_EMIT dataChanged(index(i, 0), index(i, 1));
    }
  }

  return applied();
}

bool ShortcutsTableModel::applied() const {
  return std::all_of(
      m_actions.begin(), m_actions.end(), [](auto &shortcut_data) {
        return shortcut_data.action->shortcut() == shortcut_data.key_sequence;
      });
}

bool ShortcutsTableModel::isValid() const {
  return std::all_of(m_actions.begin(), m_actions.end(),
                     [](auto &shortcut_data) { return shortcut_data.valid; });
}

int ShortcutsTableModel::rowCount(const QModelIndex &parent) const {
  return static_cast<int>(m_actions.size());
}

int ShortcutsTableModel::columnCount(const QModelIndex &parent) const {
  return 5;
}

QVariant ShortcutsTableModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  if (role == Qt::DisplayRole) {
    auto shortcut_data = m_actions.at(index.row());
    switch (index.column()) {
      case Column::ActionColumn:
        return shortcut_data.action->whatsThis();

      case Column::ShortcutColumn:
        return shortcut_data.key_sequence;

      case Column::ActionIdColumn:
        return shortcut_data.action_id;

      case Column::ValidColumn:
        return shortcut_data.valid;

      case Column::AppliedColumn:
        return shortcut_data.action->shortcut() == shortcut_data.key_sequence;

      default:
        return QVariant{};
    }
  }

  return QVariant{};
}

bool ShortcutsTableModel::setData(const QModelIndex &index,
                                  const QVariant &value, int role) {
  if (index.row() < 0 || index.row() >= rowCount(index.parent())) return false;

  if (role == Qt::DisplayRole && index.column() == Column::ShortcutColumn) {
    auto new_key_sequence = value.value<QKeySequence>();
    auto old_key_sequence = m_actions.at(index.row()).key_sequence;
    auto &shortcut_data = m_actions[index.row()];

    shortcut_data.key_sequence = new_key_sequence;

    validation({new_key_sequence, old_key_sequence});
    if (new_key_sequence != old_key_sequence) Q_EMIT dataChanged(index, index);

    return true;
  }

  return false;
}

QVariant ShortcutsTableModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
      case Column::ActionColumn:
        return tr("Action");

      case Column::ShortcutColumn:
        return tr("Shortcut");

      case Column::ActionIdColumn:
        return tr("Action Id");

      case Column::ValidColumn:
        return tr("Valid");

      case Column::AppliedColumn:
        return tr("Applied");

      default:
        return QVariant{};
    }
  }
  return QVariant{};
}

Qt::ItemFlags ShortcutsTableModel::flags(const QModelIndex &index) const {
  auto flags = QAbstractTableModel::flags(index);
  if (index.column() == Column::ShortcutColumn) flags |= Qt::ItemIsEditable;

  return flags;
}

void ShortcutsTableModel::init() {
  const auto action_ids = egnite::ActionManager::getInstance().getActionsId();
  for (const auto &action_id : action_ids) addedShortcut(action_id);
}

void ShortcutsTableModel::addedShortcut(const QString &action_id) {
  auto shortcut_data_iter = std::find_if(
      m_actions.begin(), m_actions.end(), [&action_id](auto &shortcut_data) {
        return shortcut_data.action_id == action_id;
      });

  if (shortcut_data_iter == m_actions.end()) {
    auto row = static_cast<int>(m_actions.size());
    auto action = egnite::ActionManager::getInstance().findAction(action_id);
    auto key_sequence = action->shortcut();

    beginInsertRows(QModelIndex{}, row, row);
    m_actions.push_back(ShortcutData{action, action_id, key_sequence, true});
    endInsertRows();

    validation({key_sequence});
  }
}

void ShortcutsTableModel::removedShortcut(const QString &action_id) {
  auto shortcut_data_iter = std::find_if(
      m_actions.begin(), m_actions.end(), [&action_id](auto &shortcut_data) {
        return shortcut_data.action_id == action_id;
      });

  if (shortcut_data_iter != m_actions.end()) {
    auto row =
        static_cast<int>(std::distance(m_actions.begin(), shortcut_data_iter));
    auto key_sequence = shortcut_data_iter->key_sequence;

    beginRemoveRows(QModelIndex{}, row, row);
    m_actions.erase(shortcut_data_iter);
    endRemoveRows();

    validation({key_sequence});
  }
}

void ShortcutsTableModel::validation(const QSet<QKeySequence> &key_sequences) {
  auto duplicated_shortcuts = QMultiMap<QKeySequence, int>{};
  for (auto i = 0; i < m_actions.size(); ++i) {
    if (!key_sequences.contains(m_actions[i].key_sequence)) continue;
    duplicated_shortcuts.insert(m_actions[i].key_sequence, i);
  }

  for (const auto &current_key_sequence : duplicated_shortcuts.keys()) {
    auto indexes = duplicated_shortcuts.values(current_key_sequence);
    for (auto &i : indexes) {
      const auto empty = m_actions[i].key_sequence.isEmpty();
      const auto changed =
          (indexes.size() == 1 || empty) != (m_actions[i].valid);

      if (changed) {
        m_actions[i].valid = !m_actions[i].valid;
        Q_EMIT dataChanged(index(i, 0), index(i, 1));
      }
    }
  }
}
