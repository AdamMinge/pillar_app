#ifndef PILLAR_SETTINGS_WIDGET_FACTORY_H
#define PILLAR_SETTINGS_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class SettingsWidget;

class LIB_PILLAR_API SettingsWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit SettingsWidgetFactory(QObject *parent = nullptr);
  ~SettingsWidgetFactory() override;

  [[nodiscard]] virtual std::unique_ptr<SettingsWidget> create() const = 0;
  [[nodiscard]] virtual QString getParentObjectName() const;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::SettingsWidgetFactory,
                    "org.pillar.SettingsWidgetFactory")

#endif  // PILLAR_SETTINGS_WIDGET_FACTORY_H
