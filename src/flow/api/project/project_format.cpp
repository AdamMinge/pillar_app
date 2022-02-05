/* ----------------------------------- Local -------------------------------- */
#include "flow/api/project/project_format.h"
#include "flow/api/project/project.h"
/* -------------------------------------------------------------------------- */

namespace api::project
{

  /* ------------------------------- ProjectFormat ---------------------------- */

  IProjectFormat::IProjectFormat(QObject *parent) : IFileFormat(parent) {}

  IProjectFormat::~IProjectFormat() = default;

  /* --------------------------- ReadableProjectFormat ------------------------ */

  IReadableProjectFormat::IReadableProjectFormat(QObject *parent)
      : IProjectFormat(parent)
  {}

  IReadableProjectFormat::~IReadableProjectFormat() = default;

  bool IReadableProjectFormat::save(const IProject &project,
                                    const QString &file_name, QString *error)
  {
    if (error) *error = tr("Project format is readable only");

    return false;
  }

  IReadableProjectFormat::Capabilities
  IReadableProjectFormat::getCapabilities() const
  {
    return Capability::Read;
  }

  /* --------------------------- WritableProjectFormat ------------------------ */

  IWritableProjectFormat::IWritableProjectFormat(QObject *parent)
      : IProjectFormat(parent)
  {}

  IWritableProjectFormat::~IWritableProjectFormat() = default;

  std::unique_ptr<IProject>
  IWritableProjectFormat::load(const QString &file_name, QString *error)
  {
    if (error) *error = tr("Project format is writable only");

    return nullptr;
  }

  IWritableProjectFormat::Capabilities
  IWritableProjectFormat::getCapabilities() const
  {
    return Capability::Write;
  }

}//namespace api::project
