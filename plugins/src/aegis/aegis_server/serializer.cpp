/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis_server {

ResponseSerializer::ResponseSerializer(Format format) : m_format(format) {}

ResponseSerializer::~ResponseSerializer() = default;

}  // namespace aegis_server
