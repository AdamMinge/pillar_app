/* ------------------------------------ Qt ---------------------------------- */
#include <QDesktopServices>
#include <QEvent>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QMenu>
#include <QMessageBox>
#include <QTreeView>
#include <QUrl>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/action_manager.h"
#include "flow/editor/document/document_manager.h"
#include "flow/editor/project/project_dock.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/api/project.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/file_system/file_system_proxy_model.h>
/* -------------------------------------------------------------------------- */

ProjectDock::ProjectDock(QWidget *parent)
    : QDockWidget(parent), m_current_project(nullptr),
      m_view(new QTreeView(this)), m_model(new QFileSystemModel(this)),
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
  if (m_current_project == project) return;

  m_current_project = project;

  const auto dir = m_current_project
                     ? QFileInfo{m_current_project->getFileName()}.dir()
                     : QDir{};
  auto upDir = dir;
  upDir.cdUp();

  m_model->setRootPath(dir.path());
  m_view->setRootIndex(m_proxy->mapFromSource(m_model->index(upDir.path())));
}

api::IProject *ProjectDock::getProject() const { return m_current_project; }

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
  connect(m_view, &QTreeView::activated, this, &ProjectDock::openDocument);
  connect(m_view, &QTreeView::customContextMenuRequested, this,
          &ProjectDock::openContextMenu);
}

void ProjectDock::retranslateUi() { setWindowTitle(tr("Project")); }

void ProjectDock::openFile(const QModelIndex &index)
{
  Q_ASSERT(index.isValid());
  QDesktopServices::openUrl(
    QUrl::fromLocalFile(index.data(QFileSystemModel::FilePathRole).toString()));
}

void ProjectDock::removeFile(const QModelIndex &index)
{
  const auto path = index.data(QFileSystemModel::FilePathRole).toString();
  const auto is_file = QFileInfo(path).isFile();

  const auto message_title =
    is_file ? tr("Delete File") : tr("Delete Directory");
  const auto question_message =
    is_file ? tr("Are you sure that you want to permanently delete this file?")
            : tr("Are you sure that you want to permanently delete this "
                 "directory and all its contents?");
  const auto information_message = is_file
                                     ? tr("Failed to delete the file!")
                                     : tr("Failed to delete the directory!");

  auto ret =
    QMessageBox::question(this, message_title, question_message,
                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
  {
    if (is_file ? !QFile(path).remove() : !QDir(path).removeRecursively())
      QMessageBox::information(this, message_title, information_message);
  }
}

void ProjectDock::renameFile(const QModelIndex &index)
{
  Q_ASSERT(index.isValid());
  const auto path = index.data(QFileSystemModel::FilePathRole).toString();
  // TODO Implementation
}

void ProjectDock::newDirectory()
{
  // TODO Implementation
}

void ProjectDock::openContextMenu(const QPoint &position)
{
  const auto index = m_view->indexAt(position);
  const auto file_path = index.data(QFileSystemModel::FilePathRole).toString();
  const auto directory_index =
    QFileInfo(file_path).isFile() ? index.parent() : index;

  QMenu menu;
  QMenu new_menu(tr("&New"));
  QMenu refactor_menu(tr("&Refactor"));
  QMenu open_in_menu(tr("&Open In"));

  new_menu.addAction(ActionManager::getInstance().findAction("new_document"));
  new_menu.addSeparator();
  new_menu.addAction(tr("&Directory"), [this]() { newDirectory(); });

  if (index.isValid())
  {
    auto source_root_index = m_model->index(m_model->rootPath());
    auto root_index = m_proxy->mapFromSource(source_root_index);

    if (index != root_index)
    {
      refactor_menu.addAction(tr("&Rename"),
                              [this, index]() { renameFile(index); });
      refactor_menu.addSeparator();
      refactor_menu.addAction(tr("&Delete"),
                              [this, index]() { removeFile(index); });
    }

    open_in_menu.addAction(
      tr("&Files"), [this, directory_index]() { openFile(directory_index); });

    if (QFileInfo(file_path).isFile())
      open_in_menu.addAction(tr("&System Editor"),
                             [this, index]() { openFile(index); });
  }

  if (!new_menu.isEmpty()) menu.addMenu(&new_menu);
  menu.addSeparator();
  if (!refactor_menu.isEmpty()) menu.addMenu(&refactor_menu);
  menu.addSeparator();
  if (!open_in_menu.isEmpty()) menu.addMenu(&open_in_menu);

  menu.exec(m_view->mapToGlobal(position));
}

void ProjectDock::openDocument(const QModelIndex &index)
{
  auto source_index = m_proxy->mapToSource(index);
  auto file_path = source_index.data(QFileSystemModel::FilePathRole).toString();
  auto file_info = QFileInfo(file_path);

  if (file_info.isFile())
    DocumentManager::getInstance().loadDocument(file_path);
}
