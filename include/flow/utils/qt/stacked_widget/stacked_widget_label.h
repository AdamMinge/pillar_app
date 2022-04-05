#ifndef FLOW_STACKED_WIDGET_LABEL_H
#define FLOW_STACKED_WIDGET_LABEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QList>
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

    void setHistorySize(qsizetype size);
    [[nodiscard]] qsizetype getHistorySize() const;

  Q_SIGNALS:
    void currentChanged(QWidget *widget);

  protected:
    void changeEvent(QEvent *event) override;

  private Q_SLOTS:
    void selectionChanged(
      const QItemSelection &selected, const QItemSelection &deselected);
    void modelChanged(QAbstractItemModel *model);

    void moveHistory(qsizetype direction);
    void appendToHistory(const QModelIndex &index);

  private:
    void initUi();
    void initConnections();

    void updateActions();

    void retranslateUi();

  private:
    QScopedPointer<Ui::QtStackedWidgetLabel> m_ui;
    QAbstractItemView *m_view;
    QList<QWidget *> m_history;
    qsizetype m_history_position;
    qsizetype m_history_size;
  };

}// namespace utils

#endif//FLOW_STACKED_WIDGET_LABEL_H
