#ifndef EGNITE_NEW_DOCUMENT_WIDGET_H
#define EGNITE_NEW_DOCUMENT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QMessageBox>
#include <QWidget>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/format_helper.h>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/concept.h"
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class Document;

class LIB_EGNITE_API NewDocumentWidget : public QWidget {
  Q_OBJECT

 public:
  explicit NewDocumentWidget(QWidget *parent = nullptr);
  ~NewDocumentWidget() override;

  [[nodiscard]] bool isValid() const;

  [[nodiscard]] virtual std::unique_ptr<Document> createDocument() = 0;

 Q_SIGNALS:
  void isValidChanged(bool valid);

 protected:
  template <IsDocument DOCUMENT, IsFileFormat FORMAT>
  std::unique_ptr<Document> createDocument(const QString &name,
                                           const QString &path);

  void setValid(bool valid);

 private:
  bool m_valid;
};

template <IsDocument DOCUMENT, IsFileFormat FORMAT>
std::unique_ptr<Document> NewDocumentWidget::createDocument(
    const QString &name, const QString &path) {
  auto format_helper =
      egnite::FormatHelper<FORMAT>{egnite::FileFormat::Capability::Write};
  auto format = format_helper.getFormats().isEmpty()
                    ? nullptr
                    : format_helper.getFormats().front();

  auto error = tr("Wrong document format");
  if (format) {
    auto document = DOCUMENT::create();
    document->setWriterFormat(format);
    document->setWriterFormat(format);

    const auto file_name =
        QDir(path).filePath(name + "." + format->getShortName());

    if (QFileInfo::exists(file_name)) {
      QMessageBox::critical(this, tr("Error Document Creation"), error);
      return nullptr;
    }

    if (document->save(file_name, &error)) return document;
  }

  QMessageBox::critical(this, tr("Error Document Creation"), error);
  return nullptr;
}

}  // namespace egnite

#endif  // EGNITE_NEW_DOCUMENT_WIDGET_H
