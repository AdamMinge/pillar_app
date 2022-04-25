#ifndef FLOW_NEW_DOCUMENT_WIDGET_H
#define FLOW_NEW_DOCUMENT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::document
{

  class Document;

  class LIB_FLOW_API NewDocumentWidget : public QWidget
  {
    Q_OBJECT

  public:
    explicit NewDocumentWidget(QWidget *parent = nullptr);
    ~NewDocumentWidget() override;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] virtual std::unique_ptr<Document> createDocument() = 0;

  Q_SIGNALS:
    void isValidChanged(bool valid);

  protected:
    void setValid(bool valid);

  private:
    bool m_valid;
  };

}// namespace flow::document

#endif//FLOW_NEW_DOCUMENT_WIDGET_H
