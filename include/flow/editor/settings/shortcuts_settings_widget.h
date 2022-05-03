#ifndef FLOW_SHORTCUTS_SETTINGS_WIDGET_H
#define FLOW_SHORTCUTS_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/settings/settings_widget.h>
#include <flow/libflow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class ShortcutsSettingsWidget;
}

class ShortcutsTableModel;
class ShortcutsTableDelegate;

class ShortcutsSettingsWidget : public flow::settings::SettingsWidget
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
  void contextMenu(const QPoint &pos);

  void setDefaultShortcuts(const QList<QModelIndex> &indexes);
  void clearShortcuts(const QList<QModelIndex> &indexes);

private:
  QScopedPointer<Ui::ShortcutsSettingsWidget> m_ui;

  QScopedPointer<ShortcutsTableModel> m_shortcuts_table_model;
  QScopedPointer<ShortcutsTableDelegate> m_shortcuts_table_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

class ShortcutsSettingsWidgetFactory
    : public flow::settings::SettingsWidgetFactory
{
  Q_OBJECT
  Q_INTERFACES(flow::settings::SettingsWidgetFactory)

public:
  explicit ShortcutsSettingsWidgetFactory(QObject *parent = nullptr);
  ~ShortcutsSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::settings::SettingsWidget>
  create() const override;
};

#endif//FLOW_SHORTCUTS_SETTINGS_WIDGET_H
