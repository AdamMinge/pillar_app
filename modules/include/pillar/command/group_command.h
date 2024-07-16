#ifndef PILLAR_GROUP_COMMAND_H
#define PILLAR_GROUP_COMMAND_H

/* ----------------------------------- Local -------------------------------- */
#include "pillar/command/command.h"
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class LIB_PILLAR_API GroupCommand : public Command {
 public:
  explicit GroupCommand(QString text, Command *parent = nullptr);
  ~GroupCommand() override;

  void undo() override;
  void redo() override;

  [[nodiscard]] bool canMergeWith(const Command &other) const override;
  void mergeWith(const Command &other) override;

  void addCommand(Command *command);
  void removeCommand(Command *command);
  [[nodiscard]] const QList<Command *> &getCommands() const;

 private:
  QList<Command *> m_commands;
};

}  // namespace pillar

#endif  // PILLAR_GROUP_COMMAND_H
