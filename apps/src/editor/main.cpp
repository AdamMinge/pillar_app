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
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/application.h>
#include <egnite/language_translator.h>
#include <egnite/plugin_manager.h>
#include <egnite/preferences_manager.h>
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
  egnite::PluginManager::getInstance().addObject(new ProjectFormatPro(&app));
}

static void registerDefaultSettings(QApplication &app) {
  egnite::PluginManager::getInstance().addObject(
      new GeneralSettingsWidgetFactory(&app));
  egnite::PluginManager::getInstance().addObject(
      new AppearanceSettingsWidgetFactory(&app));
  egnite::PluginManager::getInstance().addObject(
      new ShortcutsSettingsWidgetFactory(&app));
  egnite::PluginManager::getInstance().addObject(
      new PluginSettingsWidgetFactory(&app));
}

static void registerDefaultLanguageTranslators(QApplication &app) {
  egnite::PluginManager::getInstance().addObject(
      new egnite::BaseLanguageTranslator(translations::TranslationsPath, &app));
}

static void registerDefaultPlugins(QApplication &app) {
  registerDefaultFormats(app);
  registerDefaultSettings(app);
  registerDefaultLanguageTranslators(app);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char **argv) {
  egnite::Application app(argc, argv);

  qInstallMessageHandler(messagesToConsole);

  registerDefaultPlugins(app);

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
