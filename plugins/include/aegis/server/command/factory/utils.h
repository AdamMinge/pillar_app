#ifndef AEGIS_SERVER_COMMAND_FACTORY_UTILS_H
#define AEGIS_SERVER_COMMAND_FACTORY_UTILS_H

/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/factory/factory.h"
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

/* ----------------------- Helper macro to create factory ------------------- */

#define DECLARE_COMMAND_FACTORY(EXPORT_API, COMMAND)                 \
  class EXPORT_API COMMAND##Factory : public aegis::CommandFactory { \
    Q_OBJECT                                                         \
    Q_INTERFACES(aegis::CommandFactory)                              \
   public:                                                           \
    explicit COMMAND##Factory(QObject* parent = nullptr)             \
        : aegis::CommandFactory(parent) {}                           \
                                                                     \
    [[nodiscard]] std::unique_ptr<aegis::Command> create(            \
        const CommandManager& manager) const override {              \
      return std::make_unique<COMMAND>(manager);                     \
    }                                                                \
  };

#endif  // AEGIS_SERVER_COMMAND_FACTORY_UTILS_H