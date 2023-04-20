/* ----------------------------------- Local -------------------------------- */
#include "project/recent_project_list_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Flow --------------------------------- */
#include <flow/preferences_manager.h>
/* -------------------------------------------------------------------------- */

RecentProjectListModel::RecentProjectListModel(QObject *parent)
    : QAbstractListModel(parent) {
  connect(std::addressof(flow::PreferencesManager::getInstance()),
          &flow::PreferencesManager::recentProjectFilesChanged, this,
          &RecentProjectListModel::recentProjectFilesChanged);

  recentProjectFilesChanged();
}

RecentProjectListModel::~RecentProjectListModel() = default;

QVariant RecentProjectListModel::data(const QModelIndex &index,
                                      int role) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  switch (role) {
    case Qt::DisplayRole:
    case Role::ProjectNameRole:
      return QFileInfo(m_projects.at(index.row())).baseName();

    case Role::ProjectPathRole:
      return m_projects.at(index.row());

    case Qt::DecorationRole:
    case Role::ProjectIconRole:
      return getProjectIcon(index);

    case Role::ProjectLastModifiedDateRole:
      return QFileInfo(m_projects.at(index.row())).lastModified();

    default:
      return QVariant{};
  }
}

int RecentProjectListModel::rowCount(const QModelIndex &parent) const {
  return static_cast<int>(m_projects.size());
}

void RecentProjectListModel::recentProjectFilesChanged() {
  beginResetModel();
  m_projects = flow::PreferencesManager::getInstance().getRecentProjectFiles();
  endResetModel();
}

QIcon RecentProjectListModel::getProjectIcon(const QModelIndex &index) const {
  return QIcon(":/editor/images/64x64/project.png");
}
