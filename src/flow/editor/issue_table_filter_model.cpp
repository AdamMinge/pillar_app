/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/issue_table_filter_model.h"
#include "flow/editor/issue_table_model.h"
/* -------------------------------------------------------------------------- */

IssueTableFilterModel::IssueTableFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent), m_warnings_visible(true),
      m_errors_visible(true)
{}

IssueTableFilterModel::~IssueTableFilterModel() = default;

void IssueTableFilterModel::setWarningsVisible(bool visible)
{
  if (m_warnings_visible == visible) return;

  m_warnings_visible = visible;
  invalidateFilter();
}

void IssueTableFilterModel::setErrorsVisible(bool visible)
{
  if (m_errors_visible == visible) return;

  m_errors_visible = visible;
  invalidateFilter();
}

bool IssueTableFilterModel::areWarningsVisible() const
{
  return m_warnings_visible;
}

bool IssueTableFilterModel::areErrorsVisible() const
{
  return m_errors_visible;
}

bool IssueTableFilterModel::filterAcceptsRow(
  int sourceRow, const QModelIndex &sourceParent) const
{
  auto index = sourceModel()->index(sourceRow, 0, sourceParent);
  auto issue = index.data(IssueTableModel::Role::IssueRole).value<Issue>();

  if (
    (issue.getSeverity() == Issue::Severity::Warning && areWarningsVisible()) ||
    (issue.getSeverity() == Issue::Severity::Error && areErrorsVisible()))
    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);

  return false;
}
