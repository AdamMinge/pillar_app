#ifndef FLOW_SETTINGS_DIALOG_H
#define FLOW_SETTINGS_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class SettingsDialog;
}

class SettingsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = nullptr);
  ~SettingsDialog() override;

protected:
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void filterSettings(const QString& filter);

private:
  void initUi();
  void initConnections();

  [[nodiscard]] QAbstractItemModel *
  createStackedWidgetTreeModel();

  void retranslateUi();

private:
  QScopedPointer<Ui::SettingsDialog> m_ui;
};

#endif//FLOW_SETTINGS_DIALOG_H
