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

static constexpr QLatin1String parent_error =
    QLatin1String("Parent Command Error");

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
    : Command(manager) {
  m_parser.addHelpOption();
  m_parser.addOptions({
      {{"q", "query"},
       "Query that identifies the object whose parent we are looking for",
       "query"},
  });
}

ParentCommand::~ParentCommand() = default;

QString ParentCommand::getName() const { return QString("Parent"); }

QByteArray ParentCommand::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error = Response<>(ErrorMessage(parent_error, m_parser.errorText()));
    return serialize(error);
  }

  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serialize(m_finder.find(query));
  }

  auto error = Response<>(
      ErrorMessage(parent_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
