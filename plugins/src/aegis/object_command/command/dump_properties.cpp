/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/dump_properties.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* --------------------------- PropertiesDumpMessage ------------------------ */

bool PropertiesDumpMessage::operator==(
    const PropertiesDumpMessage& other) const {
  return object == other.object && properties == other.properties;
}

bool PropertiesDumpMessage::operator!=(
    const PropertiesDumpMessage& other) const {
  return object != other.object || properties != other.properties;
}

/* --------------------------- DumpPropertiesCommand ------------------------ */

DumpPropertiesCommand::DumpPropertiesCommand()
    : Command(QLatin1String("DumpProperties")) {
  m_parser.addOptions({{{"q", "query"},
                        "Query that identifies the objects we are dumping for",
                        "query"}});
  m_required_options.append("query");
}

DumpPropertiesCommand::~DumpPropertiesCommand() = default;

QByteArray DumpPropertiesCommand::exec() {
  const auto query_str = m_parser.value("query");
  const auto query = ObjectQuery::fromString(query_str);
  if (!query.isValid()) {
    auto error = Response<>(
        ErrorMessage(getError(), QLatin1String("Query has incorrect format.")));
    return serializer()->serialize(error);
  }

  return serializer()->serialize(dump(query));
}

Response<PropertiesDumpsMessage> DumpPropertiesCommand::dump(
    const ObjectQuery& query) const {
  const auto objects = searcher()->getObjects(query);

  auto message = PropertiesDumpsMessage{};
  for (const auto object : objects) {
    const auto object_id = searcher()->getId(object);
    const auto properties = getProperties(object);

    message.objects.append(
        PropertiesDumpMessage{object_id.toString(), properties});
  }

  return message;
}

QMap<QString, QVariant> DumpPropertiesCommand::getProperties(
    const QObject* object) const {
  auto meta_object = object->metaObject();
  auto properties = QMap<QString, QVariant>{};

  for (auto i = 0; i < meta_object->propertyCount(); ++i) {
    const auto name = meta_object->property(i).name();
    const auto value = object->property(name);

    properties.insert(name, value);
  }

  return properties;
}

}  // namespace aegis