#ifndef PILLAR_NEW_DOCUMENT_WIDGET_FACTORY_H
#define PILLAR_NEW_DOCUMENT_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class NewDocumentWidget;

class LIB_PILLAR_API NewDocumentWidgetFactory : public QObject {
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

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::NewDocumentWidgetFactory,
                    "org.pillar.NewDocumentWidgetFactory")

#endif  // PILLAR_NEW_DOCUMENT_WIDGET_FACTORY_H
