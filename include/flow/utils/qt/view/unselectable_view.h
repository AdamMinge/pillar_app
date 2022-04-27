#ifndef FLOW_UNSELECTABLE_VIEW_H
#define FLOW_UNSELECTABLE_VIEW_H

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
  class VIEW_API QtUnselectableView : public VIEW
  {
  public:
    explicit QtUnselectableView(QWidget *parent = nullptr);
    ~QtUnselectableView() override;

  protected:
    void mousePressEvent(QMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
  };

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  QtUnselectableView<VIEW>::QtUnselectableView(QWidget *parent) : VIEW(parent)
  {}

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
    QtUnselectableView<VIEW>::~QtUnselectableView() = default;

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  void QtUnselectableView<VIEW>::mousePressEvent(QMouseEvent *event)
  {
    if (event->buttons() != Qt::RightButton)
    {
      auto item = VIEW::indexAt(event->pos());
      auto selected = VIEW::selectionModel()->isSelected(item);

      if ((item.row() == -1 && item.column() == -1) || selected)
      {
        VIEW::selectionModel()->setCurrentIndex(
          QModelIndex(), QItemSelectionModel::ClearAndSelect);
      }
    }

    VIEW::mousePressEvent(event);
  }

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  void QtUnselectableView<VIEW>::focusOutEvent(QFocusEvent *event)
  {
    if (event->reason() != Qt::PopupFocusReason)
    {
      VIEW::selectionModel()->setCurrentIndex(
        QModelIndex(), QItemSelectionModel::ClearAndSelect);
    }

    VIEW::focusOutEvent(event);
  }

  using QtUnselectableTreeView = QtUnselectableView<QTreeView>;
  using QtUnselectableListView = QtUnselectableView<QListView>;
  using QtUnselectableTableView = QtUnselectableView<QTableView>;

}// namespace utils

#endif//FLOW_UNSELECTABLE_VIEW_H
