/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/format/project_format.h"
#include "flow/editor/project/project.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------- ProjectFormat ---------------------------- */

ProjectFormat::ProjectFormat(QObject *parent)
    : FileFormat(parent)
{
}

ProjectFormat::~ProjectFormat() = default;

/* --------------------------- ReadableProjectFormat ------------------------ */

ReadableProjectFormat::ReadableProjectFormat(QObject *parent)
    : ProjectFormat(parent)
{
}

ReadableProjectFormat::~ReadableProjectFormat() = default;

bool ReadableProjectFormat::save(const Project &project)
{
  return false;
}

ReadableProjectFormat::Capabilities ReadableProjectFormat::getCapabilities() const
{
  return Capability::Read;
}

/* --------------------------- WritableProjectFormat ------------------------ */

WritableProjectFormat::WritableProjectFormat(QObject *parent)
    : ProjectFormat(parent)
{
}

WritableProjectFormat::~WritableProjectFormat() = default;

std::unique_ptr<Project> WritableProjectFormat::load(const QString &file_name)
{
  return nullptr;
}

WritableProjectFormat::Capabilities WritableProjectFormat::getCapabilities() const
{
  return Capability::Write;
}
