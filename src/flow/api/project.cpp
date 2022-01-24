/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/project.h"
#include "flow/api/project_format.h"
/* -------------------------------------------------------------------------- */

IProject::IProject(QObject *parent)
    : QObject(parent)
{
}

IProject::~IProject() = default;
