/* ----------------------------------- Local -------------------------------- */
#include "document/new_document_dialog.h"

#include "document/new_document_widget_list_delegate.h"
#include "document/new_document_widget_list_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/document/document.h>
#include <pillar/document/new_document_widget.h>
#include <pillar/preferences_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_document_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewDocumentDialog::Preferences {
  pillar::Preference<QByteArray> new_document_dialog_geometry =
      pillar::Preference<QByteArray>("new_document_dialog/geometry");
};

/* ----------------------------- NewDocumentDialog -------------------------- */

NewDocumentDialog::NewDocumentDialog(QWidget *parent)
    : QDialog(parent),
      m_ui(new Ui::NewDocumentDialog()),
      m_preferences(new Preferences),
      m_new_document_widget_model(new NewDocumentWidgetListModel()),
      m_new_document_widget_delegate(new NewDocumentWidgetListDelegate()) {
  initUi();
  initConnections();

  if (m_new_document_widget_model->rowCount(QModelIndex{}) > 0) {
    m_ui->m_new_document_widget_list->selectionModel()->select(
        m_new_document_widget_model->index(0, 0, QModelIndex{}),
        QItemSelectionModel::ClearAndSelect);
  }

  readSettings();
  retranslateUi();
}

NewDocumentDialog::~NewDocumentDialog() { writeSettings(); }

std::unique_ptr<pillar::Document> NewDocumentDialog::create() {
  if (exec() != QDialog::Accepted) return nullptr;

  auto new_document_widget = dynamic_cast<pillar::NewDocumentWidget *>(
      m_ui->m_new_document_widget_stack->currentWidget());
  Q_ASSERT(new_document_widget);

  return new_document_widget->createDocument();
}

void NewDocumentDialog::changeEvent(QEvent *event) {
  QDialog::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NewDocumentDialog::currentChanged() {
  auto current_new_document_widget = qobject_cast<pillar::NewDocumentWidget *>(
      m_ui->m_new_document_widget_stack->currentWidget());

  if (current_new_document_widget) {
    disconnect(this, SLOT(isValidChanged(bool)));
    connect(current_new_document_widget,
            &pillar::NewDocumentWidget::isValidChanged, this,
            &NewDocumentDialog::isValidChanged);

    isValidChanged(current_new_document_widget->isValid());
  } else {
    isValidChanged(false);
  }
}

void NewDocumentDialog::isValidChanged(bool valid) {
  m_ui->m_create_button->setEnabled(valid);
}

void NewDocumentDialog::initUi() {
  m_ui->setupUi(this);

  m_ui->m_new_document_widget_list->setModel(m_new_document_widget_model.get());
  m_ui->m_new_document_widget_list->setItemDelegate(
      m_new_document_widget_delegate.get());

  m_new_document_widget_delegate->setIconSize(QSize(64, 64));
  m_new_document_widget_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_new_document_widget_delegate->setSpacing(10, 15);

  m_ui->m_new_document_widget_stack->setView(m_ui->m_new_document_widget_list);

  currentChanged();
}

void NewDocumentDialog::initConnections() {
  connect(m_ui->m_create_button, &QPushButton::clicked, this,
          &NewDocumentDialog::accept);
  connect(m_ui->m_new_document_widget_stack,
          &qtils::QtStackedWidget::currentChanged, this,
          &NewDocumentDialog::currentChanged);
}

void NewDocumentDialog::retranslateUi() {
  m_ui->retranslateUi(this);

  setWindowTitle(tr("New Document"));
}

void NewDocumentDialog::writeSettings() {
  m_preferences->new_document_dialog_geometry = saveGeometry();
}

void NewDocumentDialog::readSettings() {
  auto new_document_dialog_geometry =
      m_preferences->new_document_dialog_geometry.get();
  if (!new_document_dialog_geometry.isNull())
    restoreGeometry(new_document_dialog_geometry);
}