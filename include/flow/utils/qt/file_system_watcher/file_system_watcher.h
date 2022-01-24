#ifndef FLOW_FILE_SYSTEM_WATCHER_H
#define FLOW_FILE_SYSTEM_WATCHER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemWatcher>
#include <QScopedPointer>
#include <QSet>
#include <QTimer>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/file_system_watcher/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class FILE_SYSTEM_WATCHER_API QtFileSystemWatcher : public QObject
  {
    Q_OBJECT

  public:
    explicit QtFileSystemWatcher(QObject *parent = nullptr);
    ~QtFileSystemWatcher() override;

    void addPath(const QString &path);
    void addPaths(const QStringList &paths);

    void removePath(const QString &path);
    void removePaths(const QStringList &paths);

    [[nodiscard]] QStringList getPaths() const;
    [[nodiscard]] QStringList getFilePaths() const;
    [[nodiscard]] QStringList getDirectoryPaths() const;

    void clear();

  Q_SIGNALS:
    void fileChanged(const QString &path);
    void directoryChanged(const QString &path);
    void pathsChanged(const QStringList &paths);

  private Q_SLOTS:
    void onFileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);
    void pathsChangedTimeout();

  private:
    QFileSystemWatcher m_watcher;
    QSet<QString> m_changed_paths;
    QTimer m_changed_paths_timer;
  };

}// namespace utils

#endif//FLOW_FILE_SYSTEM_WATCHER_H
