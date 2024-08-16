/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/invoke_method.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- InvokeMethodCommand ------------------------- */

InvokeMethodCommand::InvokeMethodCommand()
    : Command(QLatin1String("InvokeMethod")) {
  m_parser.addOptions({
      {{"q", "query"},
       "Query that identifies the objects we are dumping for",
       "query"},
      {{"n", "name"}, "Name that identifies the method", "name"},
  });
  m_parser.addPositionalArgument("values",
                                 "Values we are using for the method call");

  m_required_options.append({"query", "name"});
}

InvokeMethodCommand::~InvokeMethodCommand() = default;

QByteArray InvokeMethodCommand::exec() {
  const auto query_str = m_parser.value("query");
  const auto query = ObjectQuery::fromString(query_str);
  if (!query.isValid()) {
    auto error = Response<>(ErrorMessage(
        getError(),
        QLatin1String("Query '%1' has incorrect format.").arg(query_str)));
    return serializer()->serialize(error);
  }

  const auto name = m_parser.value("name");
  const auto values = m_parser.positionalArguments();

  return serializer()->serialize(invokeMethod(query, name, values));
}

Response<> InvokeMethodCommand::invokeMethod(const ObjectQuery& query,
                                             const QString& name,
                                             const QStringList& values) {
  const auto objects = searcher()->getObjects(query);
  if (objects.empty()) return EmptyMessage{};

  auto method = getMethod(objects.front(), name);
  for (const auto object : objects) {
    const auto current_method = getMethod(object, name);

    if (!method.isValid()) {
      auto error = Response<>(ErrorMessage(
          getError(), QLatin1String("Method '%1' is unknown.").arg(name)));
      return error;
    }

    if (current_method != method) {
      auto error = Response<>(ErrorMessage(
          getError(),
          QLatin1String("Method '%1' is different for objects from query.")
              .arg(name)));
      return error;
    }
  }

  if (method.parameterCount() != values.size()) {
    auto error = Response<>(ErrorMessage(
        getError(),
        QLatin1String("Method '%1' parameters count is different from passed.")
            .arg(name)));
    return error;
  }

  auto parameters = std::array<QGenericArgument, 10>{};
  for (auto i = 0; i < method.parameterCount(); ++i) {
    const auto parameter_type = method.parameterMetaType(i);
    const auto str_parameter = values[i];
    auto parameter = QVariant::fromValue(values[i]);

    if (!parameter.convert(parameter_type)) {
      auto error = Response<>(ErrorMessage(
          getError(), QLatin1String("Method parameter '%1' is incorrect.")
                          .arg(str_parameter)));
      return error;
    }

    parameters[i] = QGenericArgument(parameter.typeName(), parameter.data());
  }

  for (auto object : objects) {
    method.invoke(object, Qt::DirectConnection, parameters[0], parameters[1],
                  parameters[2], parameters[3], parameters[4], parameters[5],
                  parameters[6], parameters[7], parameters[8], parameters[9]);
  }

  return EmptyMessage{};
}

QMetaMethod InvokeMethodCommand::getMethod(const QObject* object,
                                           const QString& name) const {
  const auto meta_object = object->metaObject();

  for (auto i = 0; i < meta_object->methodCount(); ++i) {
    const auto method = meta_object->method(i);
    if (method.name() == name.toUtf8()) {
      return method;
    }
  }

  return QMetaMethod{};
}

}  // namespace aegis