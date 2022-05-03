/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project_dock.h"
#include "flow/editor/document/new_document_dialog.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QDesktopServices>
#include <QEvent>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTreeView>
#include <QUrl>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/action_manager.h>
#include <flow/libflow/document/document.h>
#include <flow/libflow/document/document_manager.h>
#include <flow/libflow/project/project.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/file_system/file_system_proxy_model.h>
#include <flow/utils/qt/view/unselectable_view.h>
/* -------------------------------------------------------------------------- */

ProjectDock::ProjectDock(QWidget *parent)
    : QDockWidget(parent), m_current_project(nullptr),
      m_view(new utils::QtUnselectableTreeView(this)),
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

void ProjectDock::setProject(flow::project::Project *project)
{
  if (m_current_project == project) return;

  m_current_project = project;

  const auto dir = m_current_project
                     ? QFileInfo{m_current_project->getFileName()}.dir()
                     : QDir{};
  auto upDir = dir;
  upDir.cdUp();

  auto root_index = m_proxy->mapFromSource(m_model->index(dir.path()));
  auto upper_root_index = m_proxy->mapFromSource(m_model->index(upDir.path()));

  m_model->setRootPath(dir.path());
  m_view->setRootIndex(upper_root_index);
  m_view->expand(root_index);
}

flow::project::Project *ProjectDock::getProject() const
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
  m_model->setReadOnly(false);

  m_proxy->setSourceModel(m_model);

  m_view->setModel(m_proxy);
  m_view->setHeaderHidden(true);
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
  connect(
    m_view, &QTreeView::customContextMenuRequested, this,
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

  auto remove_method =
    is_file ? std::function<bool()>([&path]() { return QFile(path).remove(); })
            : ([&path]() { return QDir(path).removeRecursively(); });
  const auto message_title =
    is_file ? tr("Delete File") : tr("Delete Directory");
  const auto question_message =
    is_file ? tr("Are you sure that you want to permanently delete this file?")
            : tr("Are you sure that you want to permanently delete this "
                 "directory and all its contents?");
  const auto information_message = is_file
                                     ? tr("Failed to delete the file!")
                                     : tr("Failed to delete the directory!");

  auto ret = QMessageBox::question(
    this, message_title, question_message, QMessageBox::Yes | QMessageBox::No,
    QMessageBox::No);

  if (ret == QMessageBox::Yes)
  {
    if (!remove_method())
      QMessageBox::information(this, message_title, information_message);
  }
}

void ProjectDock::renameFile(const QModelIndex &index)
{
  Q_ASSERT(index.isValid());
  const auto file_info =
    QFileInfo{index.data(QFileSystemModel::FilePathRole).toString()};
  const auto new_name = QInputDialog::getText(
    this, tr("Rename File"), tr("New Name:"), QLineEdit::Normal,
    file_info.fileName());

  if (!new_name.isEmpty() && new_name != file_info.fileName())
  {
    if (!QFile::rename(
          file_info.filePath(),
          QFileInfo{file_info.dir(), new_name}.filePath()))
    {
      QMessageBox::information(
        this, tr("Rename File"), tr("Failed to rename the file!"));
    }
  }
}

void ProjectDock::newDirectory(const QModelIndex &index)
{
  Q_ASSERT(index.isValid());
  const auto dir = QDir{index.data(QFileSystemModel::FilePathRole).toString()};

  const auto new_name =
    QInputDialog::getText(this, tr("Create Directory"), tr("Directory Name:"));

  if (!new_name.isEmpty())
  {
    if (!dir.entryList(QStringList{} << new_name, QDir::Dirs).isEmpty())
    {
      QMessageBox::information(
        this, tr("Create Directory"),
        tr("A directory with that name already exists!"));
    } else if (!dir.mkdir(new_name))
    {
      QMessageBox::information(
        this, tr("Create Directory"), tr("Failed to create the directory!"));
    }
  }
}

void ProjectDock::openContextMenu(const QPoint &position)
{
  const auto index = m_view->currentIndex();
  const auto file_path = index.data(QFileSystemModel::FilePathRole).toString();
  const auto directory_index =
    QFileInfo(file_path).isFile() ? index.parent() : index;
  const auto valid_directory_index =
    directory_index.isValid()
      ? directory_index
      : m_proxy->mapFromSource(m_model->index(m_model->rootPath()));

  QMenu menu;
  QMenu new_menu(tr("&New"));
  QMenu refactor_menu(tr("&Refactor"));
  QMenu open_in_menu(tr("&Open In"));

  new_menu.addAction(tr("&Document"), []() {
    flow::ActionManager::getInstance().findAction("new_document")->trigger();
  });
  new_menu.addSeparator();
  new_menu.addAction(tr("&Directory"), [this, valid_directory_index]() {
    newDirectory(valid_directory_index);
  });

  if (index.isValid())
  {
    auto source_root_index = m_model->index(m_model->rootPath());
    auto root_index = m_proxy->mapFromSource(source_root_index);

    if (index != root_index)
    {
      refactor_menu.addAction(
        tr("&Rename"), [this, index]() { renameFile(index); });
      refactor_menu.addSeparator();
      refactor_menu.addAction(
        tr("&Delete"), [this, index]() { removeFile(index); });
    }

    open_in_menu.addAction(
      tr("&Files"), [this, directory_index]() { openFile(directory_index); });

    if (QFileInfo(file_path).isFile())
      open_in_menu.addAction(
        tr("&System Editor"), [this, index]() { openFile(index); });
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
    flow::document::DocumentManager::getInstance().loadDocument(file_path);
}
