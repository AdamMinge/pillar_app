/* ----------------------------------- Local -------------------------------- */
#include "project/project_reader.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/project/project.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/pointer/unique_ptr_cast.h>
#include <qtils/serializer/json_archive.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectReaderImpl -------------------------- */

class ProjectReader::ProjectReaderImpl {
 public:
  explicit ProjectReaderImpl() = default;
  ~ProjectReaderImpl() = default;

  std::unique_ptr<pillar::Project> readProject(QIODevice &device);
  bool isValid(QIODevice &device);
};

std::unique_ptr<pillar::Project> ProjectReader::ProjectReaderImpl::readProject(
    QIODevice &device) {
  auto project =
      qtils::cast_unique_ptr<pillar::Project>(pillar::Project::create());

  qtils::IJsonArchive archive(device);
  archive >> qtils::ArchiveProperty("project", project);

  return project;
}

bool ProjectReader::ProjectReaderImpl::isValid(QIODevice &device) {
  return true;
}

/* ------------------------------- ProjectReader ---------------------------- */

ProjectReader::ProjectReader()
    : m_impl(std::make_unique<ProjectReaderImpl>()) {}

ProjectReader::~ProjectReader() = default;

std::unique_ptr<pillar::Project> ProjectReader::read(QIODevice &device,
                                                     QString *error) {
  auto project = m_impl->readProject(device);
  if (!project && error) *error = QObject::tr("Failed to load project");

  return project;
}

std::unique_ptr<pillar::Project> ProjectReader::read(const QString &file_name,
                                                     QString *error) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return nullptr;
  }

  auto project = m_impl->readProject(file);
  if (!project && error) *error = QObject::tr("Failed to load project");

  return project;
}

bool ProjectReader::isValid(const QString &file_name) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
  return m_impl->isValid(file);
}

bool ProjectReader::isValid(QIODevice &device) {
  return m_impl->isValid(device);
}
