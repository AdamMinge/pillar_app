/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/issue.h"
/* -------------------------------------------------------------------------- */

namespace flow {

Issue::Issue() : Issue(Severity::Error, QString{}) {}

Issue::Issue(Severity severity, QString text, QVariant context,
             Callback callback)
    : m_severity(severity),
      m_text(std::move(text)),
      m_context(std::move(context)),
      m_callback(std::move(callback)) {}

void Issue::setContext(QVariant context) { m_context = std::move(context); }

void Issue::setCallback(Callback callback) { m_callback = std::move(callback); }

Issue::Severity Issue::getSeverity() const { return m_severity; }

QString Issue::getText() const { return m_text; }

QVariant Issue::getContext() const { return m_context; }

Issue::Callback Issue::getCallback() const { return m_callback; }

bool Issue::operator==(const Issue &other) const {
  return m_severity == other.m_severity && m_text == other.m_text &&
         m_context == other.m_context;
}

bool Issue::operator!=(const Issue &other) const {
  return m_severity != other.m_severity || m_text != other.m_text ||
         m_context != other.m_context;
}

}  // namespace flow
