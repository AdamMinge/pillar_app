#ifndef PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
#define PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/new_document_widget.h>
#include <flow/libflow/document/new_document_widget_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NewFlowDocumentWidget;
}

class FLOW_DOCUMENT_API NewFlowDocumentWidget
    : public flow::document::NewDocumentWidget
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewFlowDocumentWidget(QWidget *parent = nullptr);
  ~NewFlowDocumentWidget() override;

  [[nodiscard]] std::unique_ptr<flow::document::Document>
  createDocument() override;
  [[nodiscard]] bool isValid() const override;

  [[nodiscard]] QString getDocumentId() const override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();

private Q_SLOTS:
  void updateIsValid();

private:
  QScopedPointer<Ui::NewFlowDocumentWidget> m_ui;

  QScopedPointer<Preferences> m_preferences;
  bool m_valid;
};

class FLOW_DOCUMENT_API NewFlowDocumentWidgetFactory
    : public flow::document::NewDocumentWidgetFactory
{
  Q_OBJECT
  Q_INTERFACES(flow::document::NewDocumentWidgetFactory)

public:
  explicit NewFlowDocumentWidgetFactory(QObject *parent = nullptr);
  ~NewFlowDocumentWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::document::NewDocumentWidget>
  create() const override;
};

#endif//PLUGIN_FLOW_NEW_FLOW_DOCUMENT_WIDGET_H
