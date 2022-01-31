/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project_format_pro.h"
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_reader.h"
#include "flow/editor/project/project_writer.h"
/* -------------------------------------------------------------------------- */

ProjectFormatPro::ProjectFormatPro(QObject *parent) : IProjectFormat(parent) {}

ProjectFormatPro::~ProjectFormatPro() = default;

QString ProjectFormatPro::getNameFilter() const
{
  return tr("Project files (*.pro *.xml)");
}

QString ProjectFormatPro::getShortName() const { return QStringLiteral("pro"); }

bool ProjectFormatPro::supportsFile(const QString &filename) const
{
  if (filename.endsWith(QLatin1String(".pro"), Qt::CaseSensitive)) return true;

  if (filename.endsWith(QLatin1String(".xml"), Qt::CaseSensitive))
  {
    ProjectReader project_reader;
    return project_reader.isValid(filename);
  }

  return false;
}

std::unique_ptr<api::IProject> ProjectFormatPro::load(const QString &file_name,
                                                      QString *error)
{
  ProjectReader project_reader;
  return project_reader.read(file_name, error);
}

bool ProjectFormatPro::save(const api::IProject &project,
                            const QString &file_name, QString *error)
{
  ProjectWriter project_writer;
  return project_writer.write(dynamic_cast<const Project &>(project), file_name,
                              error);
}
