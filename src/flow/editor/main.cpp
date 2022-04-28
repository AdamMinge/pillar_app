/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
#include "flow/editor/command_line_parser.h"
#include "flow/editor/main_window.h"
#include "flow/editor/project/project_format_pro.h"
#include "flow/editor/settings/appearance_settings_widget.h"
#include "flow/editor/settings/general_settings_widget.h"
#include "flow/editor/settings/plugin_settings_widget.h"
#include "flow/editor/settings/shortcuts_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_manager.h>
#include <flow/libflow/preferences_manager.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- messagesToConsole -------------------------- */

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER =
  qInstallMessageHandler(nullptr);

static void messagesToConsole(
  QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  switch (type)
  {
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

class FlowCommandLineParser : public CommandLineParser
{
public:
  explicit FlowCommandLineParser();
  ~FlowCommandLineParser() override;

  [[nodiscard]] bool isWithoutSettings() const { return m_without_settings; };
  [[nodiscard]] QStringList getPluginsPaths() const { return m_plugins_paths; };

private:
  bool m_without_settings;
  QStringList m_plugins_paths;
};

FlowCommandLineParser::FlowCommandLineParser() : m_without_settings(false)
{
  registerOption(
    {"without-preferences"},
    QObject::tr("Execute application without loading/saving preferences"),
    [this]() { m_without_settings = true; });

  registerOption<QString>(
    {"plugins-paths"}, QObject::tr("Specified locations of plugins to load"),
    [this](auto &plugin_path) { m_plugins_paths = plugin_path.split(';'); },
    QLatin1String("paths"));
}

FlowCommandLineParser::~FlowCommandLineParser() = default;

/* -------------------------- RegisterDefaultPlugins ------------------------ */

static void registerDefaultFormats(QApplication &app)
{
  flow::PluginManager::getInstance().addObject(new ProjectFormatPro(&app));
}

static void registerDefaultSettings(QApplication &app)
{
  flow::PluginManager::getInstance().addObject(
    new GeneralSettingsWidgetFactory(&app));
  flow::PluginManager::getInstance().addObject(
    new AppearanceSettingsWidgetFactory(&app));
  flow::PluginManager::getInstance().addObject(
    new ShortcutsSettingsWidgetFactory(&app));
  flow::PluginManager::getInstance().addObject(
    new PluginSettingsWidgetFactory(&app));
}

static void registerDefaultPlugins(QApplication &app)
{
  registerDefaultFormats(app);
  registerDefaultSettings(app);
}

/* -------------------------- RegisterDefaultPlugins ------------------------ */

static void parseCommandLine(QApplication &app)
{
  FlowCommandLineParser parser;
  parser.process(app);

  if (parser.isWithoutSettings())
    flow::PreferencesManager::getInstance().setSettingsType(
      flow::PreferencesSettings::Type::Temporary);

  if (auto paths = parser.getPluginsPaths(); !paths.isEmpty())
    flow::PluginManager::getInstance().setDefaultPluginsPaths(paths);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Flow-Editor"));
  QApplication::setApplicationVersion(QLatin1String(FLOW_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Flow-Editor"));
  QApplication::setOrganizationName(QStringLiteral("Flow"));

  qInstallMessageHandler(messagesToConsole);

  parseCommandLine(app);
  registerDefaultPlugins(app);

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
