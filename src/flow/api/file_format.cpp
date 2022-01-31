/* ----------------------------------- Local -------------------------------- */
#include "flow/api/file_format.h"
/* -------------------------------------------------------------------------- */

namespace api
{

  IFileFormat::IFileFormat(QObject *parent) : QObject(parent) {}

  IFileFormat::~IFileFormat() = default;

  bool IFileFormat::hasCapabilities(Capabilities capabilities) const
  {
    return (getCapabilities() & capabilities) == capabilities;
  }

  IFileFormat::Capabilities IFileFormat::getCapabilities() const
  {
    return Capability::ReadWrite;
  }

}//namespace api
