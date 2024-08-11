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
    : Command(manager) {}

ParentCommand::~ParentCommand() = default;

QString ParentCommand::getName() const { return QString("Parent"); }

QList<QCommandLineOption> ParentCommand::getOptions() const {
  return {{{"q", "query"},
           "Query that identifies the object whose parent we are looking for",
           "query"}};
}

QByteArray ParentCommand::exec(const QCommandLineParser& parser) {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  if (parser.isSet("query")) {
    const auto query = parser.value("query");
    return serialize(m_finder.find(query));
  }

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
