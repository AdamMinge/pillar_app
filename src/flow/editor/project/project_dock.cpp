/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project_dock.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/api/project.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/file_system/file_system_proxy_model.h>
/* -------------------------------------------------------------------------- */

ProjectDock::ProjectDock(QWidget *parent)
    : QDockWidget(parent),
      m_current_project(nullptr),
      m_view(new QTreeView(this)),
      m_model(new QFileSystemModel(this)),
      m_proxy(new utils::FileSystemProxyModel(this)),
      m_icon_provider(new QFileIconProvider())
{
  setObjectName(QLatin1String("Project"));

  initUi();
  initConnections();

  retranslateUi();
}

ProjectDock::~ProjectDock() = default;

void ProjectDock::setProject(api::IProject *project)
{
  if (m_current_project == project)
    return;

  m_current_project = project;

  const auto dir = m_current_project ? QFileInfo{m_current_project->getFileName()}.dir() : QDir{};
  auto upDir = dir;
  upDir.cdUp();

  m_model->setRootPath(dir.path());
  m_view->setRootIndex(m_proxy->mapFromSource(m_model->index(upDir.path())));
}

api::IProject *ProjectDock::getProject() const
{
  return m_current_project;
}

void ProjectDock::changeEvent(QEvent *event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ProjectDock::initUi()
{
  m_model->setIconProvider(m_icon_provider.get());

  m_proxy->setSourceModel(m_model);

  m_view->setModel(m_proxy);
  m_view->setColumnHidden(1, true);
  m_view->setColumnHidden(2, true);
  m_view->setColumnHidden(3, true);
  m_view->setDragEnabled(true);
  m_view->setAcceptDrops(true);
  m_view->setDropIndicatorShown(true);
  m_view->setDragDropMode(QAbstractItemView::InternalMove);
  m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_view->setContextMenuPolicy(Qt::CustomContextMenu);

  setWidget(m_view);
}

void ProjectDock::initConnections()
{
}

void ProjectDock::retranslateUi()
{
  setWindowTitle(tr("Project"));
}