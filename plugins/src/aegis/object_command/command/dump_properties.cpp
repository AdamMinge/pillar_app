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

/* ----------------------------- PropertiesDumper --------------------------- */

PropertiesDumper::PropertiesDumper() = default;

PropertiesDumper::~PropertiesDumper() = default;

PropertiesDumper::Result PropertiesDumper::dump(const QString& id) const {
  const auto objects = searcher()->getObjects(id);

  auto message = PropertiesDumpsMessage{};
  for (const auto object : objects) {
    const auto id = searcher()->getId(object);
    const auto properties = getProperties(object);

    message.objects.append(PropertiesDumpMessage{id, properties});
  }

  return message;
}

QMap<QString, QVariant> PropertiesDumper::getProperties(
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

/* --------------------------- DumpPropertiesCommand ------------------------ */

DumpPropertiesCommand::DumpPropertiesCommand()
    : Command(QLatin1String("DumpProperties")) {
  m_parser.addOptions({{{"q", "query"},
                        "Query that identifies the objects we are dumping for",
                        "query"}});
}

DumpPropertiesCommand::~DumpPropertiesCommand() = default;

QByteArray DumpPropertiesCommand::exec() {
  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serializer()->serialize(m_dumper.dump(query));
  }

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis