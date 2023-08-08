/* ----------------------------------- Local -------------------------------- */
#include "egnite/application.h"

#include "./config.h"
#include "egnite/action_manager.h"
#include "egnite/command_line_parser.h"
#include "egnite/document/document_manager.h"
#include "egnite/issue_manager.h"
#include "egnite/language_manager.h"
#include "egnite/language_translator.h"
#include "egnite/logging_manager.h"
#include "egnite/plugin_manager.h"
#include "egnite/preferences_manager.h"
#include "egnite/project/project_manager.h"
#include "egnite/script_manager.h"
#include "egnite/style_manager.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

/* -------------------------------- Preferences ----------------------------- */

struct Application::Preferences {
  egnite::Preference<QLocale> application_language =
      egnite::Preference<QLocale>("application/language");
  egnite::Preference<QString> application_style =
      egnite::Preference<QString>("application/style");
  egnite::Preference<QStringList> application_enabled_plugins =
      egnite::Preference<QStringList>("application/enabled_plugins");
  egnite::PreferenceContainer<QKeySequence> application_shortcuts =
      egnite::PreferenceContainer<QKeySequence>("application/shortcuts");
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
  setApplicationName(QStringLiteral("Egnite-Editor"));
  setApplicationVersion(QLatin1String(EGNITE_VERSION_STR));
  setApplicationDisplayName(QStringLiteral("Egnite-Editor"));
  setOrganizationName(QStringLiteral("Egnite"));

  parseCommandLine();
  readSettings();
}

Application::~Application() {
  egnite::DocumentManager::deleteInstance();
  egnite::ProjectManager::deleteInstance();
  egnite::PluginManager::deleteInstance();
  egnite::ActionManager::deleteInstance();
  egnite::PreferencesManager::deleteInstance();
  egnite::StyleManager::deleteInstance();
  egnite::LanguageManager::deleteInstance();
  egnite::LoggingManager::deleteInstance();
  egnite::IssueManager::deleteInstance();
  egnite::ScriptManager::deleteInstance();
}

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
    egnite::PreferencesManager::getInstance().setSettingsType(
        egnite::PreferencesSettings::Type::Temporary);

  if (auto paths = libraryPaths() + parser.getPluginsPaths(); !paths.isEmpty())
    egnite::PluginManager::getInstance().setDefaultPluginsPaths(paths);
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
       egnite::PluginManager::getInstance().getDynamicPlugins()) {
    if (plugin->isEnabled()) enabled_plugins << plugin->getFileName();
  }

  m_preferences->application_enabled_plugins = enabled_plugins;
}

void Application::writeLanguage() {
  m_preferences->application_language =
      egnite::LanguageManager::getInstance().getCurrentLanguage();
}

void Application::writeStyle() {
  m_preferences->application_style =
      egnite::StyleManager::getInstance().getCurrentStyle();
}

void Application::writeShortcuts() {
  const auto actions_id = egnite::ActionManager::getInstance().getActionsId();
  for (const auto &action_id : actions_id) {
    auto action = egnite::ActionManager::getInstance().findAction(action_id);
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

  egnite::PluginManager::getInstance().loadPlugins();
  for (auto plugin : egnite::PluginManager::getInstance().getPlugins()) {
    if (enabled_plugins.contains(plugin->getFileName())) plugin->enable();
  }
}

void Application::readLanguage() {
  const auto application_language = m_preferences->application_language.get();

  auto languages =
      egnite::LanguageManager::getInstance().getAvailableLanguages();
  if (languages.contains(application_language))
    egnite::LanguageManager::getInstance().setLanguage(application_language);
  else if (languages.contains(QLocale::system()))
    egnite::LanguageManager::getInstance().setLanguage(QLocale::system());
}

void Application::readStyle() {
  auto application_style = m_preferences->application_style.get();
  if (!application_style.isEmpty())
    egnite::StyleManager::getInstance().setStyle(application_style);
}

void Application::readShortcuts() {
  const auto actions_id = egnite::ActionManager::getInstance().getActionsId();
  for (const auto &action_id : actions_id) {
    if (m_preferences->application_shortcuts.contains(action_id)) {
      auto shortcut = m_preferences->application_shortcuts.get(action_id);
      egnite::ActionManager::getInstance().setCustomShortcut(action_id,
                                                             shortcut);
    }
  }
}

}  // namespace egnite
