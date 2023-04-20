#ifndef UTILS_VIEW_MOUSE_OVER_SELECTABLE_VIEW_H
#define UTILS_VIEW_MOUSE_OVER_SELECTABLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QListView>
#include <QMouseEvent>
#include <QTableView>
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/view/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
class VIEW_API QtMouseOverSelectableView : public VIEW {
 public:
  explicit QtMouseOverSelectableView(QWidget *parent = nullptr);
  ~QtMouseOverSelectableView() override;

 protected:
  void mouseMoveEvent(QMouseEvent *event) override;
  void leaveEvent(QEvent *event) override;
};

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
QtMouseOverSelectableView<VIEW>::QtMouseOverSelectableView(QWidget *parent)
    : VIEW(parent) {}

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
    QtMouseOverSelectableView<VIEW>::~QtMouseOverSelectableView() = default;

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
void QtMouseOverSelectableView<VIEW>::mouseMoveEvent(QMouseEvent *event) {
  auto item = VIEW::indexAt(event->pos());
  VIEW::setCurrentIndex(QModelIndex{});
  VIEW::setCurrentIndex(item);

  VIEW::mouseMoveEvent(event);
}

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
void QtMouseOverSelectableView<VIEW>::leaveEvent(QEvent *event) {
  VIEW::setCurrentIndex(QModelIndex{});
  VIEW::leaveEvent(event);
}

using QtMouseOverSelectableTreeView = QtMouseOverSelectableView<QTreeView>;
using QtMouseOverSelectableListView = QtMouseOverSelectableView<QListView>;
using QtMouseOverSelectableTableView = QtMouseOverSelectableView<QTableView>;

}  // namespace utils

#endif  // UTILS_VIEW_MOUSE_OVER_SELECTABLE_VIEW_H
