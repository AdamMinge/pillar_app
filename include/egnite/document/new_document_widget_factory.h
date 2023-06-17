#ifndef EGNITE_new_DOCUMENT_WIDGET_FACTORY_H
#define EGNITE_new_DOCUMENT_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class NewDocumentWidget;

class LIB_EGNITE_API NewDocumentWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit NewDocumentWidgetFactory(QIcon icon = QIcon{},
                                    QObject* parent = nullptr);
  ~NewDocumentWidgetFactory() override;

  [[nodiscard]] virtual NewDocumentWidget* create(
      QWidget* parent = nullptr) const = 0;

  void setIcon(QIcon icon);
  [[nodiscard]] QIcon getIcon() const;

 private:
  QIcon m_icon;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::NewDocumentWidgetFactory,
                    "org.egnite.NewDocumentWidgetFactory")

#endif  // EGNITE_new_DOCUMENT_WIDGET_FACTORY_H
