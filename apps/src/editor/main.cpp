/* ----------------------------------- Local -------------------------------- */
#include "main_window.h"
#include "project/project_format_pro.h"
#include "resources.h"
#include "settings/appearance_settings_widget.h"
#include "settings/general_settings_widget.h"
#include "settings/plugin_settings_widget.h"
#include "settings/shortcuts_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/application.h>
#include <pillar/language_translator.h>
#include <pillar/plugin_manager.h>
#include <pillar/preferences_manager.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- messagesToConsole -------------------------- */

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER =
    qInstallMessageHandler(nullptr);

static void messagesToConsole(QtMsgType type, const QMessageLogContext &context,
                              const QString &msg) {
  switch (type) {
    case QtInfoMsg:
    case QtDebugMsg:
      // TODO : implementation //
      break;

    case QtWarningMsg:
      // TODO : implementation //
      break;

    case QtCriticalMsg:
      // TODO : implementation //
      break;

    default:
      break;
  }

  (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

/* -------------------------- RegisterDefaultPlugins ------------------------ */

static void registerDefaultFormats(QApplication &app) {
  pillar::PluginManager::getInstance().addObject(new ProjectFormatPro(&app));
}

static void registerDefaultSettings(QApplication &app) {
  pillar::PluginManager::getInstance().addObject(
      new GeneralSettingsWidgetFactory(&app));
  pillar::PluginManager::getInstance().addObject(
      new AppearanceSettingsWidgetFactory(&app));
  pillar::PluginManager::getInstance().addObject(
      new ShortcutsSettingsWidgetFactory(&app));
  pillar::PluginManager::getInstance().addObject(
      new PluginSettingsWidgetFactory(&app));
}

static void registerDefaultLanguageTranslators(QApplication &app) {
  pillar::PluginManager::getInstance().addObject(
      new pillar::BaseLanguageTranslator(translations::TranslationsPath, &app));
}

static void registerDefaultPlugins(QApplication &app) {
  registerDefaultFormats(app);
  registerDefaultSettings(app);
  registerDefaultLanguageTranslators(app);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char **argv) {
  pillar::Application app(argc, argv);

  qInstallMessageHandler(messagesToConsole);

  registerDefaultPlugins(app);

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
