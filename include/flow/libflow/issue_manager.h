#ifndef FLOW_ISSUE_MANAGER_H
#define FLOW_ISSUE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/issue.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_API IssueManager : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static IssueManager &getInstance();
  static void deleteInstance();

 public:
  ~IssueManager() override;

  void report(const Issue &issue);

  void clear(const QVariant &context);
  void clear();

 Q_SIGNALS:
  void onWarningReport(const flow::Issue &issue);
  void onErrorReport(const flow::Issue &issue);

  void onClear(const QVariant &context);
  void onClear();

 protected:
  explicit IssueManager();

 private:
  static QScopedPointer<IssueManager> m_instance;
};

inline void REPORT_WARNING(QString text, QVariant context = QVariant{},
                           Issue::Callback callback = Issue::Callback{}) {
  IssueManager::getInstance().report(Issue{Issue::Severity::Warning,
                                           std::move(text), std::move(context),
                                           std::move(callback)});
}

inline void REPORT_ERROR(QString text, QVariant context = QVariant{},
                         Issue::Callback callback = Issue::Callback{}) {
  IssueManager::getInstance().report(Issue{Issue::Severity::Error,
                                           std::move(text), std::move(context),
                                           std::move(callback)});
}

inline void CLEAR_REPORTS(const QVariant &context) {
  IssueManager::getInstance().clear(context);
}

}  // namespace flow

#endif  // FLOW_ISSUE_MANAGER_H
