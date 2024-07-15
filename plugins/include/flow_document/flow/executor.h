#ifndef FLOW_DOCUMENT_EXECUTOR_H
#define FLOW_DOCUMENT_EXECUTOR_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Executor {
 public:
  explicit Executor();
  ~Executor();
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_EXECUTOR_H