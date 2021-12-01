/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/priv/json_document_serializer_impl.h"
#include "flow/tools/editor/document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace priv {

JsonDocumentSerializerImpl::JsonDocumentSerializerImpl() = default;

JsonDocumentSerializerImpl::~JsonDocumentSerializerImpl() = default;

QByteArray JsonDocumentSerializerImpl::serializeFlowDocument(const FlowDocument& document) const
{
  QJsonObject scene_document_object;
  scene_document_object["type"] = static_cast<int>(document.getType());

  QJsonDocument save_game_project(scene_document_object);
  return save_game_project.toJson(QJsonDocument::Compact);
}

std::unique_ptr<FlowDocument> JsonDocumentSerializerImpl::deserializeFlowDocument(const QByteArray& array) const
{
  auto load_document = QJsonDocument::fromJson(array);

  if(load_document.isNull())
    return nullptr;

  auto document_object = load_document.object();
  auto document_type = document_object["type"];

  if(document_type.type() != QJsonValue::Double || document_type != static_cast<int>(Document::Type::Flow))
    return nullptr;

  auto scene_document = FlowDocument::create();
  return scene_document;
}

} // namespace priv

