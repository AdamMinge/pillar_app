/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/command/command.h"
/* -------------------------------------------------------------------------- */

namespace aegis_server {

Command::Command(const ResponseSerializer& serializer)
    : m_serializer(serializer) {}

Command::~Command() = default;

}  // namespace aegis_server
