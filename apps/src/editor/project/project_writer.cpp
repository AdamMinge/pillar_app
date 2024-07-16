/* ----------------------------------- Local -------------------------------- */
#include "project/project_writer.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/project/project.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/json_archive.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectWriterImpl -------------------------- */

class ProjectWriter::ProjectWriterImpl {
 public:
  explicit ProjectWriterImpl() = default;
  ~ProjectWriterImpl() = default;

  void writeProject(const pillar::Project &project, QIODevice &device);
};

void ProjectWriter::ProjectWriterImpl::writeProject(
    const pillar::Project &project, QIODevice &device) {
  qtils::OJsonArchive archive(device);
  archive << qtils::ArchiveProperty("project", project);
}

/* ------------------------------- ProjectWriter ---------------------------- */

ProjectWriter::ProjectWriter()
    : m_impl(std::make_unique<ProjectWriterImpl>()) {}

ProjectWriter::~ProjectWriter() = default;

void ProjectWriter::write(const pillar::Project &project, QIODevice &device) {
  m_impl->writeProject(project, device);
}

bool ProjectWriter::write(const pillar::Project &project,
                          const QString &file_name, QString *error) {
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return false;
  }

  m_impl->writeProject(project, file);

  if (file.error() != QFileDevice::NoError) {
    if (error) *error = file.errorString();
    return false;
  }

  file.close();
  return true;
}