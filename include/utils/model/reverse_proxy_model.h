#ifndef UTILS_MODEL_REVERSE_PROXY_MODEL_H
#define UTILS_MODEL_REVERSE_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "utils/model/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class MODEL_API QtReverseProxyModel : public QSortFilterProxyModel {
 public:
  QtReverseProxyModel(QObject *parent = nullptr);
  ~QtReverseProxyModel() override;

 protected:
  bool lessThan(const QModelIndex &source_left,
                const QModelIndex &source_right) const override;
};

}  // namespace utils

#endif  // UTILS_MODEL_REVERSE_PROXY_MODEL_H
