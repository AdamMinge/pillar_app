/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/parent.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCursor>
#include <QWidget>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- ObjectParentMessage ----------------------- */

bool ObjectParentMessage::operator==(const ObjectParentMessage& other) const {
  return object == other.object && parent == other.parent;
}

bool ObjectParentMessage::operator!=(const ObjectParentMessage& other) const {
  return object != other.object || parent != other.parent;
}

/* ------------------------------ ParentCommand ----------------------------- */

ParentCommand::ParentCommand() : Command(QLatin1String("Parent")) {
  m_parser.addOptions(
      {{{"q", "query"},
        "Query that identifies the object whose parent we are looking for",
        "query"}});
  m_required_options.append("query");
}

ParentCommand::~ParentCommand() = default;

QByteArray ParentCommand::exec() {
  const auto query = m_parser.value("query");
  return serializer()->serialize(find(query));
}

Response<ObjectsParentMessage> ParentCommand::find(const QString& id) {
  const auto objects = searcher()->getObjects(id);

  auto message = ObjectsParentMessage{};
  for (const auto object : objects) {
    const auto object_id = searcher()->getId(object);
    const auto parent = getParent(object);

    message.objects.append(ObjectParentMessage{object_id, parent});
  }

  return message;
}

QString ParentCommand::getParent(const QObject* object) const {
  const auto parent_id =
      object->parent() ? searcher()->getId(object->parent()) : "";

  return parent_id;
}

}  // namespace aegis
