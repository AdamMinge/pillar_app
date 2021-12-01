#ifndef JSON_PROJECT_SERIALIZER_IMPL_H
#define JSON_PROJECT_SERIALIZER_IMPL_H

/* ------------------------------------ Local ---------------------------------- */
#include "flow/tools/editor/document/priv/document_serializer_impl.h"
/* -------------------------------------------------------------------------- */

namespace priv
{

  class JsonDocumentSerializerImpl : public DocumentSerializerImpl
  {
  public:
    JsonDocumentSerializerImpl();
    ~JsonDocumentSerializerImpl() override;

  protected:
    [[nodiscard]] QByteArray serializeFlowDocument(const FlowDocument& document) const override;
    [[nodiscard]] std::unique_ptr<FlowDocument> deserializeFlowDocument(const QByteArray& array) const override;
  };

} // namespace priv

#endif //JSON_PROJECT_SERIALIZER_IMPL_H
