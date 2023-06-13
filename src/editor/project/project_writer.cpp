/* ----------------------------------- Local -------------------------------- */
#include "project/project_writer.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/project/project.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/xml_archive.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectWriterImpl -------------------------- */

class ProjectWriter::ProjectWriterImpl {
 public:
  explicit ProjectWriterImpl() = default;
  ~ProjectWriterImpl() = default;

  void writeProject(const egnite::Project &project, QIODevice &device);
};

void ProjectWriter::ProjectWriterImpl::writeProject(
    const egnite::Project &project, QIODevice &device) {
  utils::OXmlArchive archive(device);
  archive << utils::ArchiveProperty("project", project);
}

/* ------------------------------- ProjectWriter ---------------------------- */

ProjectWriter::ProjectWriter()
    : m_impl(std::make_unique<ProjectWriterImpl>()) {}

ProjectWriter::~ProjectWriter() = default;

void ProjectWriter::write(const egnite::Project &project, QIODevice &device) {
  m_impl->writeProject(project, device);
}

bool ProjectWriter::write(const egnite::Project &project,
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