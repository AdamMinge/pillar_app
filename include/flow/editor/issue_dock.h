#ifndef FLOW_ISSUE_DOCK_H
#define FLOW_ISSUE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class IssueDock;
}

class IssueTableModel;
class IssueTableFilterModel;

class IssueDock : public QDockWidget
{
  Q_OBJECT

public:
  explicit IssueDock(QWidget *parent = nullptr);
  ~IssueDock() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private Q_SLOTS:
  void issueActivate(const QModelIndex &index);
  void searchIssue(const QString &search);

private:
  QScopedPointer<Ui::IssueDock> m_ui;

  QScopedPointer<IssueTableModel> m_issue_model;
  QScopedPointer<IssueTableFilterModel> m_issue_filter_model;
};

#endif//FLOW_ISSUE_DOCK_H
