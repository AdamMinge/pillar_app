/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/find.h"
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

/* ------------------------------- ObjectsFinder ---------------------------- */

ObjectsFinder::ObjectsFinder() = default;

ObjectsFinder::~ObjectsFinder() = default;

ObjectsFinder::Result ObjectsFinder::find(const QString& id) {
  const auto& searcher = SearcherManager::getInstance();
  const auto objects = searcher.getObjects(id);

  auto message = FoundObjectsMessage{};
  for (const auto object : objects) {
    message.objects.append(searcher.getId(object));
  }

  return message;
}

/* ------------------------------- FindCommand ------------------------------ */

FindCommand::FindCommand(const CommandExecutor& manager) : Command(manager) {}

FindCommand::~FindCommand() = default;

QString FindCommand::getName() const { return QString("Find"); }

QList<QCommandLineOption> FindCommand::getOptions() const {
  return {
      {{"q", "query"},
       "Query that identifies the objects we are looking for",
       "query"},
  };
}

QByteArray FindCommand::exec(const QCommandLineParser& parser) {
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
