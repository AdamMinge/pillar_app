/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Serializer::Serializer(Format format, QObject* parent)
    : QObject(parent), m_format(format) {}

Serializer::~Serializer() = default;

}  // namespace aegis
