#ifndef PROJECT_SERIALIZER_IMPL_H
#define PROJECT_SERIALIZER_IMPL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* -------------------------------------------------------------------------- */

class FlowDocument;
class Document;

namespace priv
{

  class DocumentSerializerImpl
  {
  public:
    DocumentSerializerImpl();
    virtual ~DocumentSerializerImpl();

    [[nodiscard]] QByteArray serialize(const Document& document) const;
    [[nodiscard]] std::unique_ptr<Document> deserialize(const QByteArray& array) const;

  protected:
    [[nodiscard]] virtual QByteArray serializeFlowDocument(const FlowDocument& document) const = 0;
    [[nodiscard]] virtual std::unique_ptr<FlowDocument> deserializeFlowDocument(const QByteArray& array) const = 0;
  };

} // namespace priv


#endif //PROJECT_SERIALIZER_IMPL_H
