/* ----------------------------------- Local -------------------------------- */
#include "egnite/project/project_format.h"

#include "egnite/project/project.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

/* ------------------------------- ProjectFormat ---------------------------- */

ProjectFormat::ProjectFormat(QObject *parent) : FileFormat(parent) {}

ProjectFormat::~ProjectFormat() = default;

/* --------------------------- ReadableProjectFormat ------------------------ */

ReadableProjectFormat::ReadableProjectFormat(QObject *parent)
    : ProjectFormat(parent) {}

ReadableProjectFormat::~ReadableProjectFormat() = default;

bool ReadableProjectFormat::save(const Project &project,
                                 const QString &file_name, QString *error) {
  if (error) *error = tr("Project format is readable only");

  return false;
}

ReadableProjectFormat::Capabilities ReadableProjectFormat::getCapabilities()
    const {
  return Capability::Read;
}

/* --------------------------- WritableProjectFormat ------------------------ */

WritableProjectFormat::WritableProjectFormat(QObject *parent)
    : ProjectFormat(parent) {}

WritableProjectFormat::~WritableProjectFormat() = default;

std::unique_ptr<Project> WritableProjectFormat::load(const QString &file_name,
                                                     QString *error) {
  if (error) *error = tr("Project format is writable only");

  return nullptr;
}

WritableProjectFormat::Capabilities WritableProjectFormat::getCapabilities()
    const {
  return Capability::Write;
}

}  // namespace egnite
