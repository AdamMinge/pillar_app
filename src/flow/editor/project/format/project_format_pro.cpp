/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/format/project_format_pro.h"
#include "flow/editor/project/format/project_reader.h"
#include "flow/editor/project/format/project_writer.h"
#include "flow/editor/project/project.h"
/* -------------------------------------------------------------------------- */

ProjectFormatPro::ProjectFormatPro(QObject *parent)
    : ProjectFormat(parent)
{
}

ProjectFormatPro::~ProjectFormatPro() = default;

QString ProjectFormatPro::getNameFilter() const
{
  return tr("Project files (*.pro *xml)");
}

QString ProjectFormatPro::getShortName() const
{
  return QStringLiteral("pro");
}

bool ProjectFormatPro::supportsFile(const QString &filename) const
{
  if (filename.endsWith(QLatin1String(".pro"), Qt::CaseSensitive))
    return true;

  if (filename.endsWith(QLatin1String(".xml"), Qt::CaseSensitive))
    return true;// TODO implementation ( check xml body )

  return false;
}

std::unique_ptr<Project> ProjectFormatPro::load(const QString &file_name)
{
  ProjectReader project_reader;
  return project_reader.read(file_name);
}

bool ProjectFormatPro::save(const Project &project)
{
  ProjectWriter project_writer;
  return project_writer.write(project, project.getFileName());
}