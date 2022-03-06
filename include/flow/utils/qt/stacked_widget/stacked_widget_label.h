#ifndef FLOW_STACKED_WIDGET_LABEL_H
#define FLOW_STACKED_WIDGET_LABEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/stacked_widget/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class QtStackedWidgetLabel;
}

namespace utils
{

  class STACKED_WIDGET_API QtStackedWidgetLabel : public QWidget
  {
    Q_OBJECT

  public:
    explicit QtStackedWidgetLabel(QWidget *parent = nullptr);
    ~QtStackedWidgetLabel() override;

    void setView(QAbstractItemView *view);
    [[nodiscard]] const QAbstractItemView *getView() const;

  protected:
    void changeEvent(QEvent *event) override;

  private Q_SLOTS:
    void selectionChanged(
      const QItemSelection &selected, const QItemSelection &deselected);

  private:
    void initUi();
    void initConnections();

    void retranslateUi();

  private:
    QScopedPointer<Ui::QtStackedWidgetLabel> m_ui;
    QAbstractItemView *m_view;
  };

}// namespace utils

#endif//FLOW_STACKED_WIDGET_LABEL_H
