/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/project/project.h"

#include "flow/libflow/format_helper.h"
#include "flow/libflow/project/project_format.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* -------------------------------------------------------------------------- */

namespace flow {

std::unique_ptr<Project> Project::create() {
  auto project = std::unique_ptr<Project>(new Project);
  return project;
}

Project::Project(QObject *parent) : QObject(parent) {}

Project::~Project() = default;

void Project::setFileName(const QString &file_name) {
  if (m_file_name == file_name) return;

  auto old_file_name = m_file_name;
  m_file_name = file_name;

  Q_EMIT fileNameChanged(file_name, old_file_name);
}

QString Project::getFileName() const { return m_file_name; }

QString Project::getDisplayName() const {
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty()) displayName = tr("untitled");

  return displayName;
}

ProjectFormat *Project::getReaderFormat() const {
  return FormatHelper<ProjectFormat>{FileFormat::Capability::Read}
      .findFormatByShortName(m_read_format);
}

ProjectFormat *Project::getWriterFormat() const {
  return FormatHelper<ProjectFormat>{FileFormat::Capability::Write}
      .findFormatByShortName(m_write_format);
}

void Project::setReaderFormat(ProjectFormat *format) {
  Q_ASSERT(format && format->hasCapabilities(FileFormat::Capability::Read));
  m_read_format = format->getShortName();
}

void Project::setWriterFormat(ProjectFormat *format) {
  Q_ASSERT(format && format->hasCapabilities(FileFormat::Capability::Write));
  m_write_format = format->getShortName();
}

bool Project::save(const QString &file_name, QString *error) {
  auto project_format = getWriterFormat();
  if (!project_format) {
    if (error) *error = tr("Wrong project format");
    return false;
  }

  if (!project_format->save(*this, file_name, error)) return false;

  setFileName(file_name);

  Q_EMIT saved();
  return true;
}

std::unique_ptr<Project> Project::load(const QString &file_name,
                                       ProjectFormat *format, QString *error) {
  if (!format) {
    auto format_helper =
        FormatHelper<ProjectFormat>{FileFormat::Capability::Read};
    format = format_helper.findFormatByFileName(file_name);
  }

  if (!format) {
    if (error) *error = tr("Wrong project format");
    return nullptr;
  }

  auto project = format->load(file_name, error);
  if (!project) return nullptr;

  project->setFileName(file_name);

  project->setReaderFormat(format);
  if (format->hasCapabilities(FileFormat::Capability::Write))
    project->setWriterFormat(format);

  return project;
}

}  // namespace flow
