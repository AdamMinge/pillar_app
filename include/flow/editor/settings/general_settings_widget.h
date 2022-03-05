#ifndef FLOW_GENERAL_SETTINGS_WIDGET_H
#define FLOW_GENERAL_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class GeneralSettingsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GeneralSettingsWidget(QWidget *parent = nullptr);
  ~GeneralSettingsWidget() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();
};

#endif//FLOW_GENERAL_SETTINGS_WIDGET_H
