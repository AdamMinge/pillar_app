/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/project/project.h"
#include "flow/api/project/project_format.h"
/* -------------------------------------------------------------------------- */

namespace api::project
{

  IProject::IProject(QObject *parent) : QObject(parent) {}

  IProject::~IProject() = default;

}//namespace api::project
