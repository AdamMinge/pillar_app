#ifndef UTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H
#define UTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "utils/model/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class MODEL_API QtLeafFilterProxyModel : public QSortFilterProxyModel {
 public:
  QtLeafFilterProxyModel(QObject *parent = nullptr);
  ~QtLeafFilterProxyModel() override;

  bool filterAcceptsRow(int source_row,
                        const QModelIndex &source_parent) const override;
};

}  // namespace utils

#endif  // UTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H
