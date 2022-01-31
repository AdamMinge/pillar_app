/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/project.h"
#include "flow/api/project_format.h"
/* -------------------------------------------------------------------------- */

namespace api
{

  IProject::IProject(QObject *parent) : QObject(parent) {}

  IProject::~IProject() = default;

}//namespace api
