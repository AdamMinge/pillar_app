#ifndef AEGIS_SERVER_COMMAND_MANAGER_H
#define AEGIS_SERVER_COMMAND_MANAGER_H

/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <unordered_map>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class CommandFactory;
class Command;

/* ------------------------------- CommandExecutor -------------------------- */

class LIB_AEGIS_SERVER_API CommandExecutor
    : public QObject,
      public pillar::PluginListener<CommandFactory> {
  Q_OBJECT

 public:
  explicit CommandExecutor(QObject* parent = nullptr);
  ~CommandExecutor() override;

  QByteArray exec(const QByteArray& data);

  QList<Command*> getCommands() const;

 protected:
  void addedObject(CommandFactory* factory) override;
  void removedObject(CommandFactory* factory) override;

 private:
  std::unordered_map<QString, Command*> m_commands;
  std::unordered_map<CommandFactory*, std::unique_ptr<Command>>
      m_command_by_factory;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_MANAGER_H