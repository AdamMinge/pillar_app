/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamReader>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_reader.h"
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/pointer_cast/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectReaderImpl -------------------------- */

class ProjectReader::ProjectReaderImpl
{
public:
  explicit ProjectReaderImpl() = default;
  ~ProjectReaderImpl() = default;

  std::unique_ptr<Project> readProject(QIODevice &device);

private:
  std::unique_ptr<Project> readProject(QXmlStreamReader &writer);
};

std::unique_ptr<Project> ProjectReader::ProjectReaderImpl::readProject(QIODevice &device)
{
  QXmlStreamReader reader;
  reader.setDevice(&device);

  if (!(reader.readNextStartElement() && reader.name() == QStringLiteral("project")))
    return nullptr;

  return readProject(reader);
}

std::unique_ptr<Project> ProjectReader::ProjectReaderImpl::readProject(QXmlStreamReader &writer)
{
  return utils::cast_unique_ptr<Project>(Project::create());
}

/* ------------------------------- ProjectReader ---------------------------- */

ProjectReader::ProjectReader()
    : m_impl(std::make_unique<ProjectReaderImpl>())
{
}

ProjectReader::~ProjectReader() = default;

std::unique_ptr<Project> ProjectReader::read(QIODevice &device)
{
  return m_impl->readProject(device);
}

std::unique_ptr<Project> ProjectReader::read(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return nullptr;

  return m_impl->readProject(file);
}