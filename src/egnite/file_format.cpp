/* ----------------------------------- Local -------------------------------- */
#include "egnite/file_format.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

FileFormat::FileFormat(QObject *parent) : QObject(parent) {}

FileFormat::~FileFormat() = default;

bool FileFormat::hasCapabilities(Capabilities capabilities) const {
  return (getCapabilities() & capabilities) == capabilities;
}

FileFormat::Capabilities FileFormat::getCapabilities() const {
  return Capability::ReadWrite;
}

}  // namespace egnite
