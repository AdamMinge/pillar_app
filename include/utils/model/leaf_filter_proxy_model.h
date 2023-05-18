#ifndef UTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H
#define UTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "utils/model/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class MODEL_API LeafFilterProxyModel : public QSortFilterProxyModel {
 public:
  LeafFilterProxyModel(QObject *parent = nullptr);
  ~LeafFilterProxyModel() override;

  bool filterAcceptsRow(int source_row,
                        const QModelIndex &source_parent) const override;
};

}  // namespace utils

#endif  // UTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H
