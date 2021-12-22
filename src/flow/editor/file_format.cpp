/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/file_format.h"
/* -------------------------------------------------------------------------- */

FileFormat::FileFormat(QObject *parent)
    : QObject(parent)
{
}

FileFormat::~FileFormat() = default;

bool FileFormat::hasCapabilities(Capabilities capabilities) const
{
  return (getCapabilities() & capabilities) == capabilities;
}

FileFormat::Capabilities FileFormat::getCapabilities() const
{
  return Capability::ReadWrite;
}
