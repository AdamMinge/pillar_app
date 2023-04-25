#ifndef EGNITE_SETTINGS_WIDGET_FACTORY_H
#define EGNITE_SETTINGS_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class SettingsWidget;

class LIB_EGNITE_API SettingsWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit SettingsWidgetFactory(QObject *parent = nullptr);
  ~SettingsWidgetFactory() override;

  [[nodiscard]] virtual std::unique_ptr<SettingsWidget> create() const = 0;
  [[nodiscard]] virtual QString getParentObjectName() const;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::SettingsWidgetFactory,
                    "org.egnite.SettingsWidgetFactory")

#endif  // EGNITE_SETTINGS_WIDGET_FACTORY_H
