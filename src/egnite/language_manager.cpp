/* ----------------------------------- Local -------------------------------- */
#include "egnite/language_manager.h"

#include "egnite/language_translator.h"
#include "egnite/resources.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

std::unique_ptr<LanguageManager> LanguageManager::m_instance =
    std::unique_ptr<LanguageManager>(nullptr);

LanguageManager &LanguageManager::getInstance() {
  if (!m_instance) m_instance.reset(new LanguageManager);

  return *m_instance;
}

void LanguageManager::deleteInstance() { m_instance.reset(nullptr); }

LanguageManager::LanguageManager() {
  auto qt_translator = new egnite::BaseLanguageTranslator(
      translations::TranslationsPath, translations::QtTranslationsPrefix, this);
  auto egnite_translator = new egnite::BaseLanguageTranslator(
      translations::TranslationsPath, translations::EgniteTranslationsPrefix,
      this);

  addedObject(qt_translator);
  addedObject(egnite_translator);

  loadObjects();
}

LanguageManager::~LanguageManager() = default;

QList<QLocale> LanguageManager::getAvailableLanguages() const {
  return m_available_locales;
}

QLocale LanguageManager::getCurrentLanguage() const { return m_current_locale; }

bool LanguageManager::setLanguage(const QLocale &locale) {
  if (m_current_locale == locale) return true;
  if (!m_available_locales.contains(locale)) return false;

  for (auto translator : m_translators) translator->setLanguage(locale);

  Q_EMIT languageChanged(locale);
  return true;
}

void LanguageManager::addedObject(LanguageTranslator *translator) {
  m_translators.insert(translator);
  translator->setLanguage(m_current_locale);
  calculateAvailableLocales();
}

void LanguageManager::removedObject(LanguageTranslator *translator) {
  m_translators.remove(translator);
  calculateAvailableLocales();
}

void LanguageManager::calculateAvailableLocales() {
  QList<QLocale> available_locales;
  for (const auto translator : m_translators) {
    for (const auto &available_language : translator->getAvailableLanguages()) {
      if (!available_locales.contains(available_language))
        available_locales.append(available_language);
    }
  }

  if (available_locales.size() == m_available_locales.size()) return;

  m_available_locales = available_locales;
  Q_EMIT availableLanguagesChanged(m_available_locales);
}

}  // namespace egnite
