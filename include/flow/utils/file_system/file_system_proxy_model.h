#ifndef UTILS_FILE_SYSTEM_FILE_SYSTEM_PROXY_MODEL_H
#define UTILS_FILE_SYSTEM_FILE_SYSTEM_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/file_system/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class FILE_SYSTEM_API FileSystemProxyModel : public QSortFilterProxyModel {
  Q_OBJECT

 public:
  explicit FileSystemProxyModel(QObject *parent = nullptr);
  ~FileSystemProxyModel() override;

  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent) override;

 protected:
  [[nodiscard]] bool filterAcceptsRow(
      int source_row, const QModelIndex &source_parent) const override;

 private:
  [[nodiscard]] bool isSiblingOf(const QModelIndex &index,
                                 const QModelIndex &parent) const;
};

}  // namespace utils

#endif  // UTILS_FILE_SYSTEM_FILE_SYSTEM_PROXY_MODEL_H
