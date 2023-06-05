/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/create_property.h"

#include "flow_document/flow/object.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QPushButton>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_create_property.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

CreateProperty::CreateProperty(Object* object, QWidget* parent)
    : QDialog(parent), m_object(object), m_ui(new Ui::CreateProperty()) {
  setObjectName(QLatin1String("CreateProperty"));

  initUi();
  initConnections();
  updateAction();

  retranslateUi();
}

CreateProperty::~CreateProperty() = default;

QString CreateProperty::getPropertyName() const {
  return m_ui->m_property_name_edit->text();
}

QMetaType CreateProperty::getPropertyType() const {
  return QMetaType(m_ui->m_property_type_combobox->currentData().toInt());
}

void CreateProperty::changeEvent(QEvent* event) {
  QDialog::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void CreateProperty::initUi() {
  m_ui->setupUi(this);

  auto types = m_ui->m_property_type_combobox;
  types->addItem("Int", static_cast<int>(QMetaType::Int));
  types->addItem("Double", static_cast<int>(QMetaType::Double));
  types->addItem("Bool", static_cast<int>(QMetaType::Bool));
  types->addItem("Char", static_cast<int>(QMetaType::QChar));
  types->addItem("String", static_cast<int>(QMetaType::QString));
  types->addItem("Date", static_cast<int>(QMetaType::QDate));
  types->addItem("DateTime", static_cast<int>(QMetaType::QDateTime));
  types->addItem("Size", static_cast<int>(QMetaType::QSizeF));
  types->addItem("Point", static_cast<int>(QMetaType::QPointF));
  types->addItem("Time", static_cast<int>(QMetaType::QTime));
  types->addItem("Color", static_cast<int>(QMetaType::QColor));
  types->addItem("Url", static_cast<int>(QMetaType::QUrl));

  types->setCurrentIndex(0);
}

void CreateProperty::initConnections() {
  connect(m_ui->m_property_name_edit, &QLineEdit::textChanged, this,
          &CreateProperty::updateAction);
}

void CreateProperty::updateAction() {
  auto ok_button = m_ui->m_buttons->button(QDialogButtonBox::Ok);
  auto property_name = m_ui->m_property_name_edit->text();
  auto already_exist = m_object->getProperties().contains(property_name);

  ok_button->setEnabled(!property_name.isEmpty() && !already_exist);
}

void CreateProperty::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document