/* ----------------------------------- Local -------------------------------- */
#include "utils/model/reverse_proxy_model.h"
/* -------------------------------------------------------------------------- */

namespace utils {

QtReverseProxyModel::QtReverseProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {
  sort(0);
}

QtReverseProxyModel::~QtReverseProxyModel() = default;

bool QtReverseProxyModel::lessThan(const QModelIndex &source_left,
                                   const QModelIndex &source_right) const {
  return source_right.row() < source_left.row();
}

}  // namespace utils