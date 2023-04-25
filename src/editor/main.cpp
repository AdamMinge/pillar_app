/* ----------------------------------- Local -------------------------------- */
#include "../config.h"
#include "command_line_parser.h"
#include "main_window.h"
#include "project/project_format_pro.h"
#include "settings/appearance_settings_widget.h"
#include "settings/general_settings_widget.h"
#include "settings/plugin_settings_widget.h"
#include "settings/shortcuts_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* ---------------------------------- Egnite -------------------------------- */
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

/* ----------------------------- CommandLineParser -------------------------- */

class EgniteCommandLineParser : public CommandLineParser {
 public:
  explicit EgniteCommandLineParser();
  ~EgniteCommandLineParser() override;

  [[nodiscard]] bool isWithoutSettings() const { return m_without_settings; };
  [[nodiscard]] QStringList getPluginsPaths() const { return m_plugins_paths; };

 private:
  bool m_without_settings;
  QStringList m_plugins_paths;
};

EgniteCommandLineParser::EgniteCommandLineParser() : m_without_settings(false) {
  registerOption(
      {"without-preferences"},
      QObject::tr("Execute application without loading/saving preferences"),
      [this]() { m_without_settings = true; });

  registerOption<QString>(
      {"plugins-paths"}, QObject::tr("Specified locations of plugins to load"),
      [this](auto &plugin_path) { m_plugins_paths = plugin_path.split(';'); },
      QLatin1String("paths"));
}

EgniteCommandLineParser::~EgniteCommandLineParser() = default;

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

static void registerDefaultPlugins(QApplication &app) {
  registerDefaultFormats(app);
  registerDefaultSettings(app);
}

/* -------------------------- RegisterDefaultPlugins ------------------------ */

static void parseCommandLine(QApplication &app) {
  EgniteCommandLineParser parser;
  parser.process(app);

  if (parser.isWithoutSettings())
    egnite::PreferencesManager::getInstance().setSettingsType(
        egnite::PreferencesSettings::Type::Temporary);

  if (auto paths = app.libraryPaths() + parser.getPluginsPaths();
      !paths.isEmpty())
    egnite::PluginManager::getInstance().setDefaultPluginsPaths(paths);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Egnite-Editor"));
  QApplication::setApplicationVersion(QLatin1String(EGNITE_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Egnite-Editor"));
  QApplication::setOrganizationName(QStringLiteral("Egnite"));

  qInstallMessageHandler(messagesToConsole);

  parseCommandLine(app);
  registerDefaultPlugins(app);

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
