#ifndef SHORTCUTS_SETTINGS_WIDGET_H
#define SHORTCUTS_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/settings/settings_widget.h>
#include <egnite/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class ShortcutsSettingsWidget;
}

class ShortcutsTableModel;
class ShortcutsTableDelegate;

class ShortcutsSettingsWidget : public egnite::SettingsWidget {
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
  void resizeSections();
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

class ShortcutsSettingsWidgetFactory : public egnite::SettingsWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(egnite::SettingsWidgetFactory)

 public:
  explicit ShortcutsSettingsWidgetFactory(QObject *parent = nullptr);
  ~ShortcutsSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<egnite::SettingsWidget> create() const override;
};

#endif  // SHORTCUTS_SETTINGS_WIDGET_H
