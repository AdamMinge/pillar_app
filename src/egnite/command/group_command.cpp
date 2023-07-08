/* ----------------------------------- Local -------------------------------- */
#include "egnite/command/group_command.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

GroupCommand::GroupCommand(QString text, Command *parent)
    : Command(QLatin1String("GroupCommand"), parent) {
  setText(text);
}

GroupCommand::~GroupCommand() { qDeleteAll(m_commands); }

void GroupCommand::undo() {
  for (auto command_iter = m_commands.rbegin();
       command_iter != m_commands.rend(); ++command_iter)
    (*command_iter)->undo();
}

void GroupCommand::redo() {
  for (auto command_iter = m_commands.begin(); command_iter != m_commands.end();
       ++command_iter)
    (*command_iter)->undo();
}

bool GroupCommand::canMergeWith(const Command &other) const {
  auto &group_command = dynamic_cast<const GroupCommand &>(other);
  if (getCommands().count() != group_command.getCommands().count())
    return false;

  auto iter_current = QListIterator<Command *>(m_commands);
  auto iter_other = QListIterator<Command *>(group_command.m_commands);

  while (iter_current.hasNext()) {
    auto current_sub_command = iter_current.next();
    auto other_sub_command = iter_other.next();

    if (!current_sub_command->canMergeWith(*other_sub_command)) return false;
  }

  return true;
}

void GroupCommand::mergeWith(const Command &other) {
  auto &group_command = dynamic_cast<const GroupCommand &>(other);
  auto iter_current = QListIterator<Command *>(m_commands);
  auto iter_other = QListIterator<Command *>(group_command.m_commands);

  while (iter_current.hasNext()) {
    auto current_sub_command = iter_current.next();
    auto other_sub_command = iter_other.next();

    current_sub_command->mergeWith(other_sub_command);
  }
}

void GroupCommand::addCommand(Command *command) { m_commands.append(command); }

void GroupCommand::removeCommand(Command *command) {
  m_commands.removeOne(command);
}

const QList<Command *> &GroupCommand::getCommands() const { return m_commands; }

}  // namespace egnite
