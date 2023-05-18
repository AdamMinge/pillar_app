#ifndef UTILS_MODEL_FIND_H
#define UTILS_MODEL_FIND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "utils/model/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

template <typename MODEL>
MODEL* cast(QAbstractItemModel* model) {
  while (model) {
    if (auto casted_model = qobject_cast<MODEL*>(model); casted_model)
      return casted_model;

    auto proxy_model = qobject_cast<QSortFilterProxyModel*>(model);
    model = proxy_model ? proxy_model->sourceModel() : nullptr;
  }

  return nullptr;
}

QModelIndex MODEL_API mapToSourceIndex(const QModelIndex& index,
                                       QAbstractItemModel* model);

QModelIndex MODEL_API mapToSourceIndex(const QModelIndex& proxy_index,
                                       QSortFilterProxyModel* proxy_model);

QModelIndex MODEL_API mapFromSourceIndex(const QModelIndex& index,
                                         QAbstractItemModel* model);

QModelIndex MODEL_API mapFromSourceIndex(const QModelIndex& source_index,
                                         QSortFilterProxyModel* proxy_model);

}  // namespace utils

#endif  // #define UTILS_MODEL_FIND_H
