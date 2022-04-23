#ifndef PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
#define PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H

/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/api/document/new_document_widget.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NewFlowDocumentWidget;
}

class NewFlowDocumentWidget : public api::document::INewDocumentWidget
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewFlowDocumentWidget(QWidget *parent = nullptr);
  ~NewFlowDocumentWidget() override;

  [[nodiscard]] std::unique_ptr<api::document::IDocument>
  createDocument() const override;
  [[nodiscard]] bool isValid() const override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NewFlowDocumentWidget> m_ui;

  QScopedPointer<Preferences> m_preferences;
};

#endif//PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
