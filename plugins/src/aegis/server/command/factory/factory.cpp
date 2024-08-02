/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/factory/factory.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

CommandFactory::CommandFactory(QObject* parent) : QObject(parent) {}

CommandFactory::~CommandFactory() = default;

}  // namespace aegis
