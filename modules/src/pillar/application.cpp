/* ----------------------------------- Local -------------------------------- */
#include "pillar/application.h"

#include "pillar/action_manager.h"
#include "pillar/command_line_parser.h"
#include "pillar/config.h"
#include "pillar/document/document_manager.h"
#include "pillar/issue_manager.h"
#include "pillar/language_manager.h"
#include "pillar/language_translator.h"
#include "pillar/logging_manager.h"
#include "pillar/plugin_manager.h"
#include "pillar/preferences_manager.h"
#include "pillar/project/project_manager.h"
#include "pillar/script_manager.h"
#include "pillar/style_manager.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

/* -------------------------------- Preferences ----------------------------- */

struct Application::Preferences {
  pillar::Preference<QLocale> application_language =
      pillar::Preference<QLocale>("application/language");
  pillar::Preference<QString> application_style =
      pillar::Preference<QString>("application/style");
  pillar::Preference<QStringList> application_enabled_plugins =
      pillar::Preference<QStringList>("application/enabled_plugins");
  pillar::PreferenceContainer<QKeySequence> application_shortcuts =
      pillar::PreferenceContainer<QKeySequence>("application/shortcuts");
};

/* -------------------------- BaseCommandLineParser ------------------------- */

class BaseCommandLineParser : public CommandLineParser {
 public:
  explicit BaseCommandLineParser();
  ~BaseCommandLineParser() override;

  [[nodiscard]] bool isWithoutSettings() const { return m_without_settings; };
  [[nodiscard]] QStringList getPluginsPaths() const { return m_plugins_paths; };

 private:
  bool m_without_settings;
  QStringList m_plugins_paths;
};

BaseCommandLineParser::BaseCommandLineParser() : m_without_settings(false) {
  registerOption(
      {"without-preferences"},
      QObject::tr("Execute application without loading/saving preferences"),
      [this]() { m_without_settings = true; });

  registerOption<QString>(
      {"plugins-paths"}, QObject::tr("Specified locations of plugins to load"),
      [this](auto &plugin_path) { m_plugins_paths = plugin_path.split(';'); },
      QLatin1String("paths"));
}

BaseCommandLineParser::~BaseCommandLineParser() = default;

/* -------------------------------- Application ----------------------------- */

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv), m_preferences(new Preferences) {
  setApplicationName(QStringLiteral("Pillar-Editor"));
  setApplicationVersion(QLatin1String(PILLAR_VERSION_STR));
  setApplicationDisplayName(QStringLiteral("Pillar-Editor"));
  setOrganizationName(QStringLiteral("Pillar"));

  parseCommandLine();
  readSettings();
}

Application::~Application() = default;

bool Application::event(QEvent *event) {
  if (event->type() == QEvent::Quit) {
    writeSettings();
  }

  return QApplication::event(event);
}

void Application::parseCommandLine() {
  BaseCommandLineParser parser;
  parser.process(*this);

  if (parser.isWithoutSettings())
    pillar::PreferencesManager::getInstance().setSettingsType(
        pillar::PreferencesSettings::Type::Temporary);

  if (auto paths = libraryPaths() + parser.getPluginsPaths(); !paths.isEmpty())
    pillar::PluginManager::getInstance().setDefaultPluginsPaths(paths);
}

void Application::writeSettings() {
  writePlugins();
  writeLanguage();
  writeStyle();
  writeShortcuts();
}

void Application::writePlugins() {
  auto enabled_plugins = QStringList{};
  for (const auto plugin :
       pillar::PluginManager::getInstance().getDynamicPlugins()) {
    if (plugin->isEnabled()) enabled_plugins << plugin->getFileName();
  }

  m_preferences->application_enabled_plugins = enabled_plugins;
}

void Application::writeLanguage() {
  m_preferences->application_language =
      pillar::LanguageManager::getInstance().getCurrentLanguage();
}

void Application::writeStyle() {
  m_preferences->application_style =
      pillar::StyleManager::getInstance().getCurrentStyle();
}

void Application::writeShortcuts() {
  const auto actions_id = pillar::ActionManager::getInstance().getActionsId();
  for (const auto &action_id : actions_id) {
    auto action = pillar::ActionManager::getInstance().findAction(action_id);
    m_preferences->application_shortcuts.set(action_id, action->shortcut());
  }
}

void Application::readSettings() {
  readPlugins();
  readLanguage();
  readStyle();
  readShortcuts();
}

void Application::readPlugins() {
  const auto enabled_plugins = m_preferences->application_enabled_plugins.get();

  pillar::PluginManager::getInstance().loadPlugins();
  for (auto plugin : pillar::PluginManager::getInstance().getPlugins()) {
    if (enabled_plugins.contains(plugin->getFileName())) plugin->enable();
  }
}

void Application::readLanguage() {
  const auto application_language = m_preferences->application_language.get();

  auto languages =
      pillar::LanguageManager::getInstance().getAvailableLanguages();
  if (languages.contains(application_language))
    pillar::LanguageManager::getInstance().setLanguage(application_language);
  else if (languages.contains(QLocale::system()))
    pillar::LanguageManager::getInstance().setLanguage(QLocale::system());
}

void Application::readStyle() {
  auto application_style = m_preferences->application_style.get();
  if (!application_style.isEmpty())
    pillar::StyleManager::getInstance().setStyle(application_style);
}

void Application::readShortcuts() {
  const auto actions_id = pillar::ActionManager::getInstance().getActionsId();
  for (const auto &action_id : actions_id) {
    if (m_preferences->application_shortcuts.contains(action_id)) {
      auto shortcut = m_preferences->application_shortcuts.get(action_id);
      pillar::ActionManager::getInstance().setCustomShortcut(action_id,
                                                             shortcut);
    }
  }
}

}  // namespace pillar
