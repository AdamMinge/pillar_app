#ifndef AEGIS_SERVER_SETTINGS_WIDGET_H
#define AEGIS_SERVER_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/settings/settings_widget.h>
#include <pillar/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class ServerSettingsWidget;
}

namespace aegis {

class ServerSettingsWidget : public pillar::SettingsWidget {
  Q_OBJECT

 public:
  explicit ServerSettingsWidget(QWidget *parent = nullptr);
  ~ServerSettingsWidget() override;

  bool apply() override;
  [[nodiscard]] bool applied() const override;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

  void onChangeServer();
  void onChangeSniffer();

 private Q_SLOTS:
  void switchServerState(int state);
  void switchSnifferState(int state);

 private:
  QScopedPointer<Ui::ServerSettingsWidget> m_ui;
};

class ServerSettingsWidgetFactory : public pillar::SettingsWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(pillar::SettingsWidgetFactory)

 public:
  explicit ServerSettingsWidgetFactory(QObject *parent = nullptr);
  ~ServerSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<pillar::SettingsWidget> create() const override;

  [[nodiscard]] QString getParentObjectName() const override;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SETTINGS_WIDGET_H
