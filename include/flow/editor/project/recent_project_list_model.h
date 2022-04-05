#ifndef FLOW_RECENT_PROJECT_LIST_MODEL_H
#define FLOW_RECENT_PROJECT_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QIcon>
#include <QStringList>
/* -------------------------------------------------------------------------- */

class RecentProjectListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum Role
  {
    ProjectNameRole = Qt::UserRole + 1,
    ProjectPathRole,
    ProjectIconRole,
    ProjectLastModifiedDateRole,
  };

public:
  explicit RecentProjectListModel(QObject *parent = nullptr);
  ~RecentProjectListModel() override;

  [[nodiscard]] QVariant
  data(const QModelIndex &index, int role) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

private:
  [[nodiscard]] QIcon getProjectIcon(const QModelIndex &index) const;

private Q_SLOTS:
  void recentProjectFilesChanged();

private:
  QStringList m_projects;
};

#endif//FLOW_RECENT_PROJECT_LIST_MODEL_H
