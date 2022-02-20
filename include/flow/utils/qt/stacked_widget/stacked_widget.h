#ifndef FLOW_STACKED_WIDGET_H
#define FLOW_STACKED_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QStackedWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/stacked_widget/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class QtStackedWidgetTreeModel;

  class STACKED_WIDGET_API QtStackedWidget : public QStackedWidget
  {
    Q_OBJECT

  public:
    explicit QtStackedWidget(QWidget *parent = nullptr);
    ~QtStackedWidget() override;

    void setView(QAbstractItemView *view);
    [[nodiscard]] const QAbstractItemView *getView() const;

  private Q_SLOTS:
    void selectionChanged(const QItemSelection &selected,
                          const QItemSelection &deselected);
    void modelChanged(QAbstractItemModel *model);

  private:
    [[nodiscard]] static QList<QWidget *>
    getStackedWidgets(const QtStackedWidgetTreeModel *model);

  private:
    QAbstractItemView *m_view;
  };

}// namespace utils

#endif//FLOW_STACKED_WIDGET_H
