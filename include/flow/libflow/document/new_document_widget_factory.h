#ifndef FLOW_new_DOCUMENT_WIDGET_FACTORY_H
#define FLOW_new_DOCUMENT_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class NewDocumentWidget;

class LIB_FLOW_API NewDocumentWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit NewDocumentWidgetFactory(QIcon icon = QIcon{},
                                    QObject *parent = nullptr);
  ~NewDocumentWidgetFactory() override;

  [[nodiscard]] virtual std::unique_ptr<NewDocumentWidget> create() const = 0;

  void setIcon(QIcon icon);
  [[nodiscard]] QIcon getIcon() const;

 private:
  QIcon m_icon;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::NewDocumentWidgetFactory,
                    "org.flow.NewDocumentWidgetFactory")

#endif  // FLOW_new_DOCUMENT_WIDGET_FACTORY_H
