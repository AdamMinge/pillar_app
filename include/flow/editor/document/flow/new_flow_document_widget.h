#ifndef FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
#define FLOW_NEW_FLOW_DOCUMENT_WIDGET_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/new_document_widget.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NewFlowDocumentWidget;
}

class NewFlowDocumentWidget : public NewDocumentWidget
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewFlowDocumentWidget(QWidget *parent = nullptr);
  ~NewFlowDocumentWidget() override;

  [[nodiscard]] std::unique_ptr<api::IDocument> createDocument() const override;
  [[nodiscard]] bool isValid() const override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NewFlowDocumentWidget> m_ui;

  QScopedPointer<Preferences> m_preferences;
};

#endif//FLOW_NEW_FLOW_DOCUMENT_WIDGET_H