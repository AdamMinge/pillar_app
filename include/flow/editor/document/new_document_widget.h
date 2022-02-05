#ifndef FLOW_FLOW_DOCUMENT_WIDGET_H
#define FLOW_FLOW_DOCUMENT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace api::document
{
  class IDocument;
}

class NewDocumentWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NewDocumentWidget(QWidget *parent = nullptr);
  ~NewDocumentWidget() override;

  [[nodiscard]] virtual std::unique_ptr<api::document::IDocument>
  createDocument() const = 0;
  [[nodiscard]] virtual bool isValid() const = 0;

Q_SIGNALS:
  void isValidChanged(bool valid);
};

#endif//FLOW_FLOW_DOCUMENT_WIDGET_H
