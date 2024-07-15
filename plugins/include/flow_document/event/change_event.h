#ifndef FLOW_DOCUMENT_CHANGE_EVENT_H
#define FLOW_DOCUMENT_CHANGE_EVENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API ChangeEvent {
 public:
  explicit ChangeEvent(QString type);
  virtual ~ChangeEvent();

  [[nodiscard]] QString getType() const;

 private:
  QString m_type;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_EVENT_H
