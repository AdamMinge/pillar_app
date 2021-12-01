/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/priv/document_serializer_impl.h"
#include "flow/tools/editor/document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace priv {

DocumentSerializerImpl::DocumentSerializerImpl() = default;

DocumentSerializerImpl::~DocumentSerializerImpl() = default;

QByteArray DocumentSerializerImpl::serialize(const Document& document) const
{
  if(auto scene_document = dynamic_cast<const FlowDocument*>(std::addressof(document)); scene_document)
    return serializeFlowDocument(*scene_document);

  return QByteArray{};
}

std::unique_ptr<Document> DocumentSerializerImpl::deserialize(const QByteArray& array) const
{
  if(auto scene_document = deserializeFlowDocument(array); scene_document)
    return scene_document;

  return nullptr;
}

} // namespace priv

