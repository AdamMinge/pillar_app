#ifndef FLOW_DOCUMENT_NEW_FLOW_DOCUMENT_WIDGET_H
#define FLOW_DOCUMENT_NEW_FLOW_DOCUMENT_WIDGET_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/document/new_document_widget.h>
#include <pillar/document/new_document_widget_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class NewFlowDocumentWidget;
}

namespace flow_document {

/* --------------------------- NewFlowDocumentWidget ------------------------ */

class FLOW_DOCUMENT_API NewFlowDocumentWidget
    : public pillar::NewDocumentWidget {
  Q_OBJECT

 private:
  struct Preferences;

 public:
  explicit NewFlowDocumentWidget(QWidget *parent = nullptr);
  ~NewFlowDocumentWidget() override;

  [[nodiscard]] std::unique_ptr<pillar::Document> createDocument() override;

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

/* ----------------------- NewFlowDocumentWidgetFactory --------------------- */

class FLOW_DOCUMENT_API NewFlowDocumentWidgetFactory
    : public pillar::NewDocumentWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(pillar::NewDocumentWidgetFactory)

 public:
  explicit NewFlowDocumentWidgetFactory(QObject *parent = nullptr);
  ~NewFlowDocumentWidgetFactory() override;

  [[nodiscard]] pillar::NewDocumentWidget *create(
      QWidget *parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NEW_FLOW_DOCUMENT_WIDGET_H
