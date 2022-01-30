#ifndef FLOW_FILE_SYSTEM_PROXY_MODEL_H
#define FLOW_FILE_SYSTEM_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/file_system/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class FileSystemProxyModel : public QSortFilterProxyModel
  {
    Q_OBJECT

  public:
    explicit FileSystemProxyModel(QObject *parent = nullptr);
    ~FileSystemProxyModel() override;

  protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

  private:
    [[nodiscard]] bool isSiblingOf(const QModelIndex &index, const QModelIndex &parent) const;
  };

}// namespace utils

#endif//FLOW_FILE_SYSTEM_PROXY_MODEL_H
