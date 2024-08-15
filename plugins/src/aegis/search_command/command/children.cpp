/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/children.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCursor>
#include <QWidget>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- ObjectChildrenMessage ----------------------- */

bool ObjectChildrenMessage::operator==(
    const ObjectChildrenMessage& other) const {
  return object == other.object && children == other.children;
}

bool ObjectChildrenMessage::operator!=(
    const ObjectChildrenMessage& other) const {
  return object != other.object || children != other.children;
}

/* ------------------------------- ChildrenFinder --------------------------- */

ChildrenFinder::ChildrenFinder() = default;

ChildrenFinder::~ChildrenFinder() = default;

ChildrenFinder::Result ChildrenFinder::find(const QString& id) {
  const auto objects = searcher()->getObjects(id);

  auto message = ObjectsChildrenMessage{};
  for (const auto object : objects) {
    const auto object_id = searcher()->getId(object);
    const auto children = getChildren(object);

    message.objects.append(ObjectChildrenMessage{object_id, children});
  }

  return message;
}

QStringList ChildrenFinder::getChildren(const QObject* object) const {
  auto children = QStringList{};
  for (const auto child : object->children()) {
    const auto child_id = searcher()->getId(child);
    children.append(child_id);
  }

  return children;
}

/* ------------------------------ ChildrenCommand --------------------------- */

ChildrenCommand::ChildrenCommand() : Command(QLatin1String("Children")) {
  m_parser.addOptions(
      {{{"q", "query"},
        "Query that identifies the object whose children we are looking "
        "for",
        "query"}});
}

ChildrenCommand::~ChildrenCommand() = default;

QByteArray ChildrenCommand::exec() {
  if (m_parser.isSet("query")) {
    const auto query = m_parser.value("query");
    return serializer()->serialize(m_finder.find(query));
  }

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis
