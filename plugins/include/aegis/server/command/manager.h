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

class ResponseSerializer;
class ObjectSearcher;

class CommandFactory;
class Command;

/* ------------------------------- CommandManager --------------------------- */

class LIB_AEGIS_SERVER_API CommandManager
    : public pillar::PluginListener<CommandFactory> {
 public:
  explicit CommandManager();
  ~CommandManager() override;

  QByteArray exec(const QByteArray& data);

  ResponseSerializer& getSerializer() const;
  ObjectSearcher& getSearcher() const;

 protected:
  void addedObject(CommandFactory* factory) override;
  void removedObject(CommandFactory* factory) override;

 private:
  std::unique_ptr<ResponseSerializer> m_serializer;
  std::unique_ptr<ObjectSearcher> m_searcher;

  std::unordered_map<QString, Command*> m_commands;
  std::unordered_map<CommandFactory*, std::unique_ptr<Command>>
      m_command_by_factory;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_MANAGER_H