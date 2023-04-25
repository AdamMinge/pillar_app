/* ----------------------------------- Local -------------------------------- */
#include "settings/plugin_list_model.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

/* ------------------------------ PluginListModel --------------------------- */

PluginListModel::PluginListModel(QObject *parent) : QAbstractListModel(parent) {
  const auto plugins = egnite::PluginManager::getInstance().getPlugins();
  for (auto &plugin : plugins)
    m_plugins.emplace_back(std::make_pair(plugin, plugin->isEnabled()));
}

PluginListModel::~PluginListModel() = default;

bool PluginListModel::apply() {
  std::for_each(m_plugins.begin(), m_plugins.end(), [](auto &plugin_pair) {
    if (plugin_pair.first->isEnabled() != plugin_pair.second) {
      auto apply_fun = plugin_pair.second ? &egnite::Plugin::enable
                                          : &egnite::Plugin::disable;
      (plugin_pair.first->*apply_fun)();
    }
  });

  return applied();
}

bool PluginListModel::applied() const {
  return std::all_of(m_plugins.begin(), m_plugins.end(), [](auto &plugin_pair) {
    return plugin_pair.first->isEnabled() == plugin_pair.second;
  });
}

bool PluginListModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (index.row() < 0 || index.row() >= rowCount(index.parent())) return false;

  if (role == Role::PluginStateRole) {
    auto applied_before = applied();
    m_plugins.at(index.row()).second = value.toBool();
    auto applied_after = applied();

    if (applied_before != applied_after) Q_EMIT appliedChanged(applied_after);
    return true;
  }

  return false;
}

QVariant PluginListModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  switch (auto plugin_pair = m_plugins.at(index.row()); role) {
    case Qt::DisplayRole:
    case Role::PluginName:
      return plugin_pair.first->getName();

    case Role::PluginDescription:
      return plugin_pair.first->getDescription();

    case Role::PluginVersion:
      return plugin_pair.first->getVersion();

    case Qt::DecorationRole:
    case Role::PluginIcon:
      return plugin_pair.first->getIcon();

    case Role::PluginFileNameRole:
      return plugin_pair.first->getFileName();

    case Role::PluginStateRole:
      return plugin_pair.second;

    default:
      return QVariant{};
  }
}

Qt::ItemFlags PluginListModel::flags(const QModelIndex &index) const {
  auto flags = QAbstractListModel::flags(index);
  flags |= Qt::ItemIsEditable;

  return flags;
}

int PluginListModel::rowCount(const QModelIndex &parent) const {
  return static_cast<int>(m_plugins.size());
}

/* --------------------------- StaticPluginListModel ------------------------ */

StaticPluginListModel::StaticPluginListModel(QObject *parent)
    : PluginListModel(parent) {
  m_plugins.erase(std::remove_if(m_plugins.begin(), m_plugins.end(),
                                 [](auto &plugin_pair) {
                                   return !plugin_pair.first->isStatic();
                                 }),
                  m_plugins.end());
}

StaticPluginListModel::~StaticPluginListModel() = default;

/* --------------------------- DynamicPluginListModel ----------------------- */

DynamicPluginListModel::DynamicPluginListModel(QObject *parent)
    : PluginListModel(parent) {
  m_plugins.erase(std::remove_if(m_plugins.begin(), m_plugins.end(),
                                 [](auto &plugin_pair) {
                                   return !plugin_pair.first->isDynamic();
                                 }),
                  m_plugins.end());
}

DynamicPluginListModel::~DynamicPluginListModel() = default;