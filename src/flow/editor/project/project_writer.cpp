/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamWriter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_writer.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectWriterImpl -------------------------- */

class ProjectWriter::ProjectWriterImpl
{
public:
  explicit ProjectWriterImpl() = default;
  ~ProjectWriterImpl() = default;

  void writeProject(const Project &project, QIODevice &device);

private:
  void writeProject(QXmlStreamWriter &writer, const Project &project);
};

void ProjectWriter::ProjectWriterImpl::writeProject(const Project &project, QIODevice &device)
{
  QXmlStreamWriter writer(&device);

  writer.writeStartDocument();
  writeProject(writer, project);
  writer.writeEndDocument();
}

void ProjectWriter::ProjectWriterImpl::writeProject(QXmlStreamWriter &writer, const Project &project)
{
  writer.writeStartElement(QStringLiteral("project"));

  writer.writeEndElement();
}

/* ------------------------------- ProjectWriter ---------------------------- */

ProjectWriter::ProjectWriter()
    : m_impl(std::make_unique<ProjectWriterImpl>())
{
}

ProjectWriter::~ProjectWriter() = default;

void ProjectWriter::write(const Project &project, QIODevice &device)
{
  m_impl->writeProject(project, device);
}

bool ProjectWriter::write(const Project &project, const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;

  m_impl->writeProject(project, file);

  if (file.error() != QFileDevice::NoError)
    return false;

  file.close();
  return true;
}