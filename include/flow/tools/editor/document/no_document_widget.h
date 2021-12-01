#ifndef FLOW_NO_DOCUMENT_WIDGET_H
#define FLOW_NO_DOCUMENT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

namespace Ui { class NoDocumentWidget; }
class DocumentListModel;
class DocumentListDelegate;

class NoDocumentWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NoDocumentWidget(QWidget* parent = nullptr);
  ~NoDocumentWidget() override;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void openDocument(const QModelIndex& index);
  void searchDocument(const QString& search);

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NoDocumentWidget> m_ui;
  QScopedPointer<DocumentListModel> m_documents_model;
  QScopedPointer<DocumentListDelegate> m_documents_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

#endif //FLOW_NO_DOCUMENT_WIDGET_H
