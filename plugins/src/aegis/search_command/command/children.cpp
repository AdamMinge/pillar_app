/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/children.h"
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

static constexpr QLatin1String children_error =
    QLatin1String("Children Command Error");

/* ------------------------------- ChildrenFinder --------------------------- */

ChildrenFinder::ChildrenFinder() = default;

ChildrenFinder::~ChildrenFinder() = default;

ChildrenFinder::Result ChildrenFinder::find(const QString& id) {
  const auto& searcher = SearcherManager::getInstance();
  const auto objects = searcher.getObjects(id);

  auto message = FoundChildrenMessage{};
  for (const auto object : objects) {
    const auto object_id = searcher.getId(object);

    auto children = QStringList{};
    for (const auto child : object->children()) {
      const auto child_id = searcher.getId(child);
      children.append(child_id);
    }

    message.children.insert(object_id, children);
  }

  return message;
}

/* ------------------------------ ChildrenCommand --------------------------- */

ChildrenCommand::ChildrenCommand(const CommandExecutor& manager)
    : Command(manager) {
  m_parser.addHelpOption();
  m_parser.addOptions({
      {{"q", "query"},
       "Query that identifies the object whose children we are looking for",
       "query"},
  });
}

ChildrenCommand::~ChildrenCommand() = default;

QString ChildrenCommand::getName() const { return QString("Children"); }

QByteArray ChildrenCommand::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error = Response<>(ErrorMessage(children_error, m_parser.errorText()));
    return serialize(error);
  }

  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serialize(m_finder.find(query));
  }

  auto error = Response<>(ErrorMessage(
      children_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
