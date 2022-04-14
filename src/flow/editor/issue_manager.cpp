/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/issue_manager.h"
#include "flow/editor/issue_table_model.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<IssueManager> IssueManager::m_instance =
  QScopedPointer<IssueManager>(nullptr);

IssueManager &IssueManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new IssueManager);

  return *m_instance;
}

void IssueManager::deleteInstance() { m_instance.reset(nullptr); }

IssueManager::IssueManager() = default;

IssueManager::~IssueManager() = default;

void IssueManager::report(const Issue &issue)
{
  switch (issue.getSeverity())
  {
    case Issue::Severity::Error:
      Q_EMIT onWarningReport(issue);
      break;

    case Issue::Severity::Warning:
      Q_EMIT onErrorReport(issue);
      break;
  }
}

void IssueManager::clear(const QVariant &context) { Q_EMIT onClear(context); }

void IssueManager::clear() { Q_EMIT onClear(); }
