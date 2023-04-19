#ifndef FLOW_SETTINGS_WIDGET_FACTORY_H
#define FLOW_SETTINGS_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class SettingsWidget;

class LIB_FLOW_API SettingsWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit SettingsWidgetFactory(QObject *parent = nullptr);
  ~SettingsWidgetFactory() override;

  [[nodiscard]] virtual std::unique_ptr<SettingsWidget> create() const = 0;
  [[nodiscard]] virtual QString getParentObjectName() const;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::SettingsWidgetFactory,
                    "org.flow.SettingsWidgetFactory")

#endif  // FLOW_SETTINGS_WIDGET_FACTORY_H
