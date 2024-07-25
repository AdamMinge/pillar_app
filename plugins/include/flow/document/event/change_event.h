#ifndef FLOW_DOCUMENT_CHANGE_EVENT_H
#define FLOW_DOCUMENT_CHANGE_EVENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API ChangeEvent {
 public:
  explicit ChangeEvent(QString type);
  virtual ~ChangeEvent();

  [[nodiscard]] QString getType() const;

 private:
  QString m_type;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_CHANGE_EVENT_H
