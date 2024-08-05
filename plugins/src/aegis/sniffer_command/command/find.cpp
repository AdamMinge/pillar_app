/* ----------------------------------- Local -------------------------------- */
#include "aegis/sniffer_command/command/find.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCursor>
#include <QWidget>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/manager.h>
#include <aegis/server/searcher/searcher.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

static constexpr QLatin1String find_error = QLatin1String("Find Command Error");

/* ---------------------------------- Finder -------------------------------- */

Finder::Finder(const ObjectSearcher& searcher) : m_searcher(searcher) {}

Finder::~Finder() = default;

Finder::Result Finder::find(const QString& id) {
  const auto objects = m_searcher.getObjects(id);

  auto message = FoundObjectsMessage{};
  for (const auto object : objects) {
    message.objects.append(m_searcher.getId(object));
  }

  return message;
}

/* ------------------------------- FindCommand ------------------------------ */

FindCommand::FindCommand(const CommandManager& manager)
    : Command(manager), m_finder(getManager().getSearcher()) {
  m_parser.addHelpOption();
  m_parser.addOptions({
      {{"q", "query"}, "Search using query", "query"},
  });
}

FindCommand::~FindCommand() = default;

QString FindCommand::getName() const { return QString("Find"); }

QByteArray FindCommand::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error = Response<>(ErrorMessage(find_error, m_parser.errorText()));
    return serialize(error);
  }

  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serialize(m_finder.find(query));
  }

  auto error = Response<>(
      ErrorMessage(find_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
