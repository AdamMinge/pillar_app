/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/file_system/file_system_proxy_model.h"
/* -------------------------------------------------------------------------- */

namespace utils
{
  FileSystemProxyModel::FileSystemProxyModel(QObject *parent)
      : QSortFilterProxyModel(parent)
  {
  }

  FileSystemProxyModel::~FileSystemProxyModel() = default;

  bool FileSystemProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
  {
    auto model = qobject_cast<QFileSystemModel *>(sourceModel());
    auto index = model->index(source_row, 0, source_parent);
    auto rootIndex = model->index(model->rootPath());

    if (!rootIndex.isValid())
      return false;

    return (index.isValid() && index == rootIndex) || !isSiblingOf(index, rootIndex);
  }

  bool FileSystemProxyModel::isSiblingOf(const QModelIndex &index, const QModelIndex &parent) const
  {
    if (!index.isValid() || !parent.isValid())
      return false;

    QModelIndex sibling;
    int row = 0;
    do
    {
      sibling = parent.sibling(row, 0);
      if (sibling == index)
        return true;

      ++row;

    } while (sibling.isValid());

    return false;
  }

}// namespace utils
