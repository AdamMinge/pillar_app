#ifndef APPEARANCE_SETTINGS_WIDGET_H
#define APPEARANCE_SETTINGS_WIDGET_H

/* ----------------------------------- Flow --------------------------------- */
#include <flow/settings/settings_widget.h>
#include <flow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class AppearanceSettingsWidget;
}

class AppearanceSettingsWidget : public flow::SettingsWidget {
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
  void languageChanged(const QString &language);
  void styleChanged(const QString &style);

 private:
  QScopedPointer<Ui::AppearanceSettingsWidget> m_ui;
};

class AppearanceSettingsWidgetFactory : public flow::SettingsWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::SettingsWidgetFactory)

 public:
  explicit AppearanceSettingsWidgetFactory(QObject *parent = nullptr);
  ~AppearanceSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::SettingsWidget> create() const override;
  [[nodiscard]] QString getParentObjectName() const override;
};

#endif  // APPEARANCE_SETTINGS_WIDGET_H
