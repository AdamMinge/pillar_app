#ifndef UTILS_COLOR_COLOR_H
#define UTILS_COLOR_COLOR_H

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

#endif  // UTILS_COLOR_COLOR_H
