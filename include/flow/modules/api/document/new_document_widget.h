#ifndef FLOW_INTERFACE_NEW_DOCUMENT_WIDGET_H
#define FLOW_INTERFACE_NEW_DOCUMENT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace api::document
{

  class IDocument;

  class INewDocumentWidget : public QWidget
  {
    Q_OBJECT

  public:
    explicit INewDocumentWidget(QWidget *parent = nullptr);
    ~INewDocumentWidget() override;

    [[nodiscard]] virtual std::unique_ptr<IDocument> createDocument() const = 0;
    [[nodiscard]] virtual bool isValid() const = 0;

  Q_SIGNALS:
    void isValidChanged(bool valid);
  };

}// namespace api::document

#endif//FLOW_INTERFACE_NEW_DOCUMENT_WIDGET_H
