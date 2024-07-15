#ifndef EGNITE_ISSUE_H
#define EGNITE_ISSUE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QString>
#include <QVariant>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LIB_EGNITE_API Issue {
 public:
  enum class Severity;
  using Callback = std::function<void()>;

 public:
  explicit Issue();
  explicit Issue(Severity severity, QString text, QVariant context = QVariant{},
                 Callback callback = Callback{});

  void setContext(QVariant context);
  void setCallback(Callback callback);

  [[nodiscard]] Severity getSeverity() const;
  [[nodiscard]] QString getText() const;
  [[nodiscard]] QVariant getContext() const;
  [[nodiscard]] Callback getCallback() const;

  [[nodiscard]] bool operator==(const Issue &other) const;
  [[nodiscard]] bool operator!=(const Issue &other) const;

 private:
  Severity m_severity;
  QString m_text;
  QVariant m_context;
  Callback m_callback;
};

enum class Issue::Severity { Warning, Error };

}  // namespace egnite

#endif  // EGNITE_ISSUE_H
