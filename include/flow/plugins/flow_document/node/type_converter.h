#ifndef FLOW_TYPE_CONVERTER_H
#define FLOW_TYPE_CONVERTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class NodeData;

class FLOW_DOCUMENT_API TypeConverter : public QObject {
  Q_OBJECT

 public:
  explicit TypeConverter() = default;
  ~TypeConverter() override = default;

  [[nodiscard]] virtual std::unique_ptr<NodeData> convert(
      const NodeData &data) = 0;
};

}  // namespace plugin::flow_document

#endif  // FLOW_TYPE_CONVERTER_H
