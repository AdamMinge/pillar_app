/* ----------------------------------- Local -------------------------------- */
#include "pillar/command/command.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

Command::Command(QString name, Command *parent)
    : QUndoCommand(parent), m_name(std::move(name)) {}

Command::~Command() = default;

bool Command::mergeWith(const QUndoCommand *other) {
  auto command = dynamic_cast<const Command *>(other);
  if (!canMergeWith(*command)) return false;

  mergeWith(*command);
  return true;
}

bool Command::canMergeWith(const Command &other) const { return false; }

void Command::mergeWith(const Command &other) { Q_UNUSED(other); }

int Command::id() const {
  return static_cast<int>(std::hash<QString>{}(m_name));
}

QString Command::name() const { return m_name; }

}  // namespace pillar
