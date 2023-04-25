#ifndef FLOW_DOCUMENT_NEW_FLOW_DOCUMENT_WIDGET_H
#define FLOW_DOCUMENT_NEW_FLOW_DOCUMENT_WIDGET_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/document/new_document_widget.h>
#include <egnite/document/new_document_widget_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class NewFlowDocumentWidget;
}

namespace flow_document {

class FLOW_DOCUMENT_API NewFlowDocumentWidget
    : public egnite::NewDocumentWidget {
  Q_OBJECT

 private:
  struct Preferences;

 public:
  explicit NewFlowDocumentWidget(QWidget *parent = nullptr);
  ~NewFlowDocumentWidget() override;

  [[nodiscard]] std::unique_ptr<egnite::Document> createDocument() override;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void retranslateUi();

 private Q_SLOTS:
  void validate();

 private:
  QScopedPointer<Ui::NewFlowDocumentWidget> m_ui;
  QScopedPointer<Preferences> m_preferences;
};

class FLOW_DOCUMENT_API NewFlowDocumentWidgetFactory
    : public egnite::NewDocumentWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(egnite::NewDocumentWidgetFactory)

 public:
  explicit NewFlowDocumentWidgetFactory(QObject *parent = nullptr);
  ~NewFlowDocumentWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<egnite::NewDocumentWidget> create()
      const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NEW_FLOW_DOCUMENT_WIDGET_H
