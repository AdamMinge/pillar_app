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
  const auto query = m_parser.value("query");
  return serializer()->serialize(find(query));
}

Response<FoundObjectsMessage> FindCommand::find(const QString& id) {
  const auto objects = searcher()->getObjects(id);

  auto message = FoundObjectsMessage{};
  for (const auto object : objects) {
    message.objects.append(searcher()->getId(object));
  }

  return message;
}

}  // namespace aegis
