/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamReader>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_reader.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectReaderImpl -------------------------- */

class ProjectReader::ProjectReaderImpl
{
public:
  explicit ProjectReaderImpl() = default;
  ~ProjectReaderImpl() = default;

  std::unique_ptr<api::IProject> readProject(QIODevice &device);

private:
  std::unique_ptr<api::IProject> readProject(QXmlStreamReader &writer);
};

std::unique_ptr<api::IProject> ProjectReader::ProjectReaderImpl::readProject(QIODevice &device)
{
  QXmlStreamReader reader;
  reader.setDevice(&device);

  if (!(reader.readNextStartElement() && reader.name() == QStringLiteral("project")))
    return nullptr;

  return readProject(reader);
}

std::unique_ptr<api::IProject> ProjectReader::ProjectReaderImpl::readProject(QXmlStreamReader &writer)
{
  return Project::create();
}

/* ------------------------------- ProjectReader ---------------------------- */

ProjectReader::ProjectReader()
    : m_impl(std::make_unique<ProjectReaderImpl>())
{
}

ProjectReader::~ProjectReader() = default;

std::unique_ptr<api::IProject> ProjectReader::read(QIODevice &device)
{
  return m_impl->readProject(device);
}

std::unique_ptr<api::IProject> ProjectReader::read(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return nullptr;

  return m_impl->readProject(file);
}