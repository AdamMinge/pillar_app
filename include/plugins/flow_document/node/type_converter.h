#ifndef FLOW_TYPE_CONVERTER_H
#define FLOW_TYPE_CONVERTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeData;

class FLOW_DOCUMENT_API TypeConverter : public QObject {
  Q_OBJECT

 public:
  explicit TypeConverter() = default;
  ~TypeConverter() override = default;

  [[nodiscard]] virtual std::unique_ptr<NodeData> convert(
      const NodeData &data) = 0;
};

}  // namespace flow_document

#endif  // FLOW_TYPE_CONVERTER_H
