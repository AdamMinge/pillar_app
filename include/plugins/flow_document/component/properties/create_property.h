#ifndef FLOW_DOCUMENT_CREATE_PROPERTY_H
#define FLOW_DOCUMENT_CREATE_PROPERTY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class CreateProperty;
}

namespace flow_document {

class Object;

class FLOW_DOCUMENT_API CreateProperty : public QDialog {
  Q_OBJECT

 public:
  explicit CreateProperty(Object* object, QWidget* parent = nullptr);
  ~CreateProperty() override;

  [[nodiscard]] QString getPropertyName() const;
  [[nodiscard]] QMetaType getPropertyType() const;

 protected:
  void changeEvent(QEvent* event) override;

 private:
  void initUi();
  void initConnections();
  void updateAction();

  void retranslateUi();

 private:
  Object* m_object;
  QScopedPointer<Ui::CreateProperty> m_ui;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CREATE_PROPERTY_H