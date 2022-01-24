/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/format_helper.h"
#include "flow/editor/project/project.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/api/project_format.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<api::IProject> Project::create()
{
  auto project = std::unique_ptr<Project>(new Project);
  return project;
}

Project::Project(QObject *parent)
    : IProject(parent)
{
}

Project::~Project() = default;

void Project::setFileName(const QString &file_name)
{
  if (m_file_name == file_name)
    return;

  auto old_file_name = m_file_name;
  m_file_name = file_name;

  Q_EMIT fileNameChanged(file_name, old_file_name);
}

QString Project::getFileName() const
{
  return m_file_name;
}

QString Project::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled");

  return displayName;
}

api::IProjectFormat *Project::getReaderFormat() const
{
  return FormatHelper<api::IProjectFormat>{api::IFileFormat::Capability::Read}.findFormatByShortName(m_read_format);
}

api::IProjectFormat *Project::getWriterFormat() const
{
  return FormatHelper<api::IProjectFormat>{api::IFileFormat::Capability::Write}.findFormatByShortName(m_write_format);
}

void Project::setReaderFormat(api::IProjectFormat *format)
{
  Q_ASSERT(format && format->hasCapabilities(api::IFileFormat::Capability::Read));
  m_read_format = format->getShortName();
}

void Project::setWriterFormat(api::IProjectFormat *format)
{
  Q_ASSERT(format && format->hasCapabilities(api::IFileFormat::Capability::Write));
  m_write_format = format->getShortName();
}

bool Project::save(const QString &file_name, QString *error)
{
  auto project_format = getWriterFormat();

  if (!project_format)
  {
    if (error) *error = tr("Wrong project format");
    return false;
  }


  if (!project_format->save(*this, file_name, error))
    return false;

  setFileName(file_name);

  Q_EMIT saved();
  return true;
}

std::unique_ptr<api::IProject> Project::load(const QString &file_name, api::IProjectFormat *format, QString *error)
{
  if (!format)
  {
    auto format_helper = FormatHelper<api::IProjectFormat>{api::IFileFormat::Capability::Read};
    format = format_helper.findFormatByFileName(file_name);
  }

  if (!format)
  {
    if (error) *error = tr("Wrong project format");
    return nullptr;
  }

  return format->load(file_name, error);
}
