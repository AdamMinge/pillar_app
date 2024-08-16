/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/find.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCursor>
#include <QWidget>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------- FindCommand ------------------------------ */

FindCommand::FindCommand() : Command(QLatin1String("Find")) {
  m_parser.addOptions({{{"q", "query"},
                        "Query that identifies the objects we are looking for",
                        "query"}});
  m_required_options.append("query");
}

FindCommand::~FindCommand() = default;

QByteArray FindCommand::exec() {
  const auto query_str = m_parser.value("query");
  const auto query = ObjectQuery::fromString(query_str);
  if (!query.isValid()) {
    auto error = Response<>(
        ErrorMessage(getError(), QLatin1String("Query has incorrect format.")));
    return serializer()->serialize(error);
  }

  return serializer()->serialize(find(query));
}

Response<FoundObjectsMessage> FindCommand::find(
    const ObjectQuery& query) const {
  const auto objects = searcher()->getObjects(query);

  auto message = FoundObjectsMessage{};
  for (const auto object : objects) {
    message.objects.append(searcher()->getId(object).toString());
  }

  return message;
}

}  // namespace aegis
