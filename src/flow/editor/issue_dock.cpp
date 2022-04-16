/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/issue_dock.h"
#include "flow/editor/issue_table_filter_model.h"
#include "flow/editor/issue_table_model.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_issue_dock.h"
/* -------------------------------------------------------------------------- */

IssueDock::IssueDock(QWidget *parent)
    : QDockWidget(parent), m_ui(new Ui::IssueDock()),
      m_issue_model(new IssueTableModel()),
      m_issue_filter_model(new IssueTableFilterModel())
{
  initUi();
  initConnections();

  retranslateUi();
}

IssueDock::~IssueDock() = default;

void IssueDock::changeEvent(QEvent *event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void IssueDock::initUi()
{
  m_ui->setupUi(this);

  m_issue_filter_model->setSourceModel(m_issue_model.get());
  m_issue_filter_model->sort(IssueTableModel::Column::SeverityColumn);
  m_issue_filter_model->setFilterKeyColumn(
    IssueTableModel::Column::DescriptionColumn);

  m_ui->m_issues_view->setModel(m_issue_filter_model.get());
  m_ui->m_issues_view->horizontalHeader()->setSectionResizeMode(
    IssueTableModel::Column::DescriptionColumn, QHeaderView::Stretch);
  m_ui->m_issues_view->horizontalHeader()->setSectionResizeMode(
    IssueTableModel::Column::SeverityColumn,
    QHeaderView::ResizeMode::ResizeToContents);
  m_ui->m_issues_view->horizontalHeader()->setSectionResizeMode(
    IssueTableModel::Column::OccurrencesColumn,
    QHeaderView::ResizeMode::ResizeToContents);
}

void IssueDock::initConnections()
{
  connect(
    m_ui->m_issues_view, &QTableView::activated, this,
    &IssueDock::issueActivate);
  connect(
    m_ui->m_search_issue, &QLineEdit::textChanged, this,
    &IssueDock::searchIssue);

  connect(
    m_ui->m_show_warnings_button, &QToolButton::clicked,
    m_issue_filter_model.get(), &IssueTableFilterModel::setWarningsVisible);
  connect(
    m_ui->m_show_errors_button, &QToolButton::clicked,
    m_issue_filter_model.get(), &IssueTableFilterModel::setErrorsVisible);
}

void IssueDock::retranslateUi() { m_ui->retranslateUi(this); }

void IssueDock::issueActivate(const QModelIndex &index)
{
  const auto issue =
    m_issue_filter_model->data(index, IssueTableModel::Role::IssueRole)
      .value<Issue>();
  if (auto callback = issue.getCallback(); callback) callback();
}

void IssueDock::searchIssue(const QString &search)
{
  m_issue_filter_model->setFilterWildcard(search);
}
