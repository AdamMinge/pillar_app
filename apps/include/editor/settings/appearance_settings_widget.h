#ifndef APPEARANCE_SETTINGS_WIDGET_H
#define APPEARANCE_SETTINGS_WIDGET_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/settings/settings_widget.h>
#include <pillar/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class AppearanceSettingsWidget;
}

class AppearanceSettingsWidget : public pillar::SettingsWidget {
  Q_OBJECT

 public:
  explicit AppearanceSettingsWidget(QWidget *parent = nullptr);
  ~AppearanceSettingsWidget() override;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private Q_SLOTS:
  void languageChanged(int index);
  void styleChanged(const QString &style);
  void availableLanguagesChanged(const QList<QLocale> &locales);

 private:
  QScopedPointer<Ui::AppearanceSettingsWidget> m_ui;
};

class AppearanceSettingsWidgetFactory : public pillar::SettingsWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(pillar::SettingsWidgetFactory)

 public:
  explicit AppearanceSettingsWidgetFactory(QObject *parent = nullptr);
  ~AppearanceSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<pillar::SettingsWidget> create() const override;
  [[nodiscard]] QString getParentObjectName() const override;
};

#endif  // APPEARANCE_SETTINGS_WIDGET_H
