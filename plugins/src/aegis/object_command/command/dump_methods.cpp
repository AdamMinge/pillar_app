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

/* ------------------------------ MethodsDumper ----------------------------- */

MethodsDumper::MethodsDumper() = default;

MethodsDumper::~MethodsDumper() = default;

MethodsDumper::Result MethodsDumper::dump(const QString& id) const {
  const auto objects = searcher()->getObjects(id);

  auto message = MethodsDumpsMessage{};
  for (const auto object : objects) {
    const auto id = searcher()->getId(object);
    const auto methods = getMethods(object);

    message.objects.append(MethodsDumpMessage{id, methods});
  }

  return message;
}

QStringList MethodsDumper::getMethods(const QObject* object) const {
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

/* ---------------------------- DumpMethodsCommand -------------------------- */

DumpMethodsCommand::DumpMethodsCommand()
    : Command(QLatin1String("DumpMethods")) {
  m_parser.addOptions({{{"q", "query"},
                        "Query that identifies the objects we are dumping for",
                        "query"}});
}

DumpMethodsCommand::~DumpMethodsCommand() = default;

QByteArray DumpMethodsCommand::exec() {
  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serializer()->serialize(m_dumper.dump(query));
  }

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis