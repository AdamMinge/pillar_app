/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/dump_methods.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- MethodsDumpMessage -------------------------- */

bool MethodsDumpMessage::operator==(const MethodsDumpMessage& other) const {
  return object == other.object && methods == other.methods;
}

bool MethodsDumpMessage::operator!=(const MethodsDumpMessage& other) const {
  return object != other.object || methods != other.methods;
}

/* ---------------------------- DumpMethodsCommand -------------------------- */

DumpMethodsCommand::DumpMethodsCommand()
    : Command(QLatin1String("DumpMethods")) {
  m_parser.addOptions({{{"q", "query"},
                        "Query that identifies the objects we are dumping for",
                        "query"}});
  m_required_options.append("query");
}

DumpMethodsCommand::~DumpMethodsCommand() = default;

QByteArray DumpMethodsCommand::exec() {
  const auto query_str = m_parser.value("query");
  const auto query = ObjectQuery::fromString(query_str);
  if (!query.isValid()) {
    auto error = Response<>(ErrorMessage(
        getError(),
        QLatin1String("Query '%1' has incorrect format.").arg(query_str)));
    return serializer()->serialize(error);
  }

  return serializer()->serialize(dump(query));
}

Response<MethodsDumpsMessage> DumpMethodsCommand::dump(
    const ObjectQuery& query) const {
  const auto objects = searcher()->getObjects(query);

  auto message = MethodsDumpsMessage{};
  for (const auto object : objects) {
    const auto object_id = searcher()->getId(object);
    const auto methods = getMethods(object);

    message.objects.append(MethodsDumpMessage{object_id.toString(), methods});
  }

  return message;
}

QStringList DumpMethodsCommand::getMethods(const QObject* object) const {
  auto meta_object = object->metaObject();
  auto methods = QStringList{};

  for (auto i = 0; i < meta_object->methodCount(); ++i) {
    const auto method = meta_object->method(i);
    const auto method_name = method.name();

    auto parameters = QStringList{};
    for (auto j = 0; j < method.parameterCount(); ++j) {
      const auto parameter_type = method.parameterTypeName(j);

      parameters.append(QLatin1String("%1").arg(parameter_type));
    }

    methods.append(
        QLatin1String("%1(%2)").arg(method_name).arg(parameters.join(", ")));
  }

  return methods;
}

}  // namespace aegis