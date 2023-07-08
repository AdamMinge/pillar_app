#ifndef EGNITE_GROUP_COMMAND_H
#define EGNITE_GROUP_COMMAND_H

/* ----------------------------------- Local -------------------------------- */
#include "egnite/command/command.h"
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LIB_EGNITE_API GroupCommand : public Command {
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

}  // namespace egnite

#endif  // EGNITE_GROUP_COMMAND_H
