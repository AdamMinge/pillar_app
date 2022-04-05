#ifndef FLOW_SETTINGS_DIALOG_H
#define FLOW_SETTINGS_DIALOG_H

/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/dialog/dialog_with_url_links.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class SettingsDialog;
}

class SettingsDialog : public utils::QtDialogWithUrlLinks<SettingsDialog>
{
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = nullptr);
  ~SettingsDialog() override;

public Q_SLOTS:
  void setUrl(const QUrl &url) override;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void filterSettings(const QString &filter);

  void ok();
  void apply();
  void cancel();

  void currentChanged(QWidget *widget);

private:
  void initUi();
  void initConnections();

  void retranslateUi();

  [[nodiscard]] QAbstractItemModel *createStackedWidgetTreeModel();

private:
  QScopedPointer<Ui::SettingsDialog> m_ui;
};

#endif//FLOW_SETTINGS_DIALOG_H
