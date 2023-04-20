#ifndef PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
#define PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H

/* ----------------------------------- Flow --------------------------------- */
#include <flow/document/new_document_widget.h>
#include <flow/document/new_document_widget_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class NewFlowDocumentWidget;
}

namespace flow_document {

class FLOW_DOCUMENT_API NewFlowDocumentWidget : public flow::NewDocumentWidget {
  Q_OBJECT

 private:
  struct Preferences;

 public:
  explicit NewFlowDocumentWidget(QWidget *parent = nullptr);
  ~NewFlowDocumentWidget() override;

  [[nodiscard]] std::unique_ptr<flow::Document> createDocument() override;

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
    : public flow::NewDocumentWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::NewDocumentWidgetFactory)

 public:
  explicit NewFlowDocumentWidgetFactory(QObject *parent = nullptr);
  ~NewFlowDocumentWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::NewDocumentWidget> create()
      const override;
};

}  // namespace flow_document

#endif  // PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
