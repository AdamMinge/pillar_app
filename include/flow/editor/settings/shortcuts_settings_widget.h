#ifndef FLOW_SHORTCUTS_SETTINGS_WIDGET_H
#define FLOW_SHORTCUTS_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class ShortcutsSettingsWidget;
}

class ShortcutsTableModel;
class ShortcutsTableDelegate;

class ShortcutsSettingsWidget : public SettingsWidget
{
  Q_OBJECT

public:
  explicit ShortcutsSettingsWidget(QWidget *parent = nullptr);
  ~ShortcutsSettingsWidget() override;

  bool apply() override;
  [[nodiscard]] bool applied() const override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private Q_SLOTS:
  void searchAction(const QString &search);

private:
  QScopedPointer<Ui::ShortcutsSettingsWidget> m_ui;

  QScopedPointer<ShortcutsTableModel> m_shortcuts_table_model;
  QScopedPointer<ShortcutsTableDelegate> m_shortcuts_table_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

#endif//FLOW_SHORTCUTS_SETTINGS_WIDGET_H
