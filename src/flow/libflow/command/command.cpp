/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/command/command.h"
/* -------------------------------------------------------------------------- */

namespace flow::command
{

  Command::Command(Command *parent) : QUndoCommand(parent) {}

  Command::~Command() = default;

  bool Command::mergeWith(const QUndoCommand *other)
  {
    auto command = dynamic_cast<const Command *>(other);
    if (!canMergeWith(*command)) return false;

    mergeWith(*command);
    return true;
  }

  bool Command::canMergeWith(const Command &other) const { return false; }

  void Command::mergeWith(const Command &other) { Q_UNUSED(other); }

}// namespace flow::command
