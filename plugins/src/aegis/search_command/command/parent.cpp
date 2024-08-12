/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/parent.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCursor>
#include <QWidget>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/searcher/searcher_manager.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* -------------------------------- ParentFinder ---------------------------- */

ParentFinder::ParentFinder() = default;

ParentFinder::~ParentFinder() = default;

ParentFinder::Result ParentFinder::find(const QString& id) {
  const auto& searcher = SearcherManager::getInstance();
  const auto objects = searcher.getObjects(id);

  auto message = FoundParentMessage{};
  for (const auto object : objects) {
    const auto object_id = searcher.getId(object);
    const auto parent_id =
        object->parent() ? searcher.getId(object->parent()) : "";

    message.parents.insert(object_id, parent_id);
  }

  return message;
}

/* ------------------------------ ParentCommand ----------------------------- */

ParentCommand::ParentCommand(const CommandExecutor& manager)
    : Command(QLatin1String("Parent"), manager) {
  m_parser.addOptions(
      {{{"q", "query"},
        "Query that identifies the object whose parent we are looking for",
        "query"}});
}

ParentCommand::~ParentCommand() = default;

QByteArray ParentCommand::exec() {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serialize(m_finder.find(query));
  }

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
