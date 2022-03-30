#ifndef FLOW_MOUSE_OVER_SELECTABLE_VIEW_H
#define FLOW_MOUSE_OVER_SELECTABLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QListView>
#include <QMouseEvent>
#include <QTableView>
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/view/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  class VIEW_API QtMouseOverSelectableView : public VIEW
  {
  public:
    explicit QtMouseOverSelectableView(QWidget *parent = nullptr);
    ~QtMouseOverSelectableView() override;

  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
  };

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  QtMouseOverSelectableView<VIEW>::QtMouseOverSelectableView(QWidget *parent)
      : VIEW(parent)
  {}

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
    QtMouseOverSelectableView<VIEW>::~QtMouseOverSelectableView() = default;

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  void QtMouseOverSelectableView<VIEW>::mouseMoveEvent(QMouseEvent *event)
  {
    auto item = VIEW::indexAt(event->pos());
    auto selected = VIEW::selectionModel()->isSelected(item);

    if (!item.isValid())
    {
      VIEW::clearSelection();
      VIEW::selectionModel()->setCurrentIndex(
        QModelIndex{}, QItemSelectionModel::SelectCurrent);

    } else if (!selected)
    {
      VIEW::selectionModel()->setCurrentIndex(
        QModelIndex{}, QItemSelectionModel::SelectCurrent);
      VIEW::selectionModel()->setCurrentIndex(
        item, QItemSelectionModel::SelectCurrent);
    }

    VIEW::mouseMoveEvent(event);
  }

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  void QtMouseOverSelectableView<VIEW>::leaveEvent(QEvent *event)
  {
    VIEW::clearSelection();
    VIEW::selectionModel()->setCurrentIndex(
      QModelIndex{}, QItemSelectionModel::SelectCurrent);

    VIEW::leaveEvent(event);
  }

  using QtMouseOverSelectableTreeView = QtMouseOverSelectableView<QTreeView>;
  using QtMouseOverSelectableListView = QtMouseOverSelectableView<QListView>;
  using QtMouseOverSelectableTableView = QtMouseOverSelectableView<QTableView>;

}// namespace utils

#endif//FLOW_MOUSE_OVER_SELECTABLE_VIEW_H
