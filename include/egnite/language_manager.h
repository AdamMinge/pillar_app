#ifndef EGNITE_LANGUAGE_MANAGER_H
#define EGNITE_LANGUAGE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLocale>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
#include "egnite/plugin_listener.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LanguageTranslator;

class LIB_EGNITE_API LanguageManager
    : public QObject,
      public PluginListener<LanguageTranslator> {
  Q_OBJECT

 public:
  static LanguageManager &getInstance();
  static void deleteInstance();

 public:
  ~LanguageManager() override;

  [[nodiscard]] QList<QLocale> getAvailableLanguages() const;
  [[nodiscard]] QLocale getCurrentLanguage() const;

 public Q_SLOTS:
  bool setLanguage(const QLocale &locale);

 Q_SIGNALS:
  void languageChanged(const QLocale &locale);
  void availableLanguagesChanged(const QList<QLocale> &locales);

 private:
  explicit LanguageManager();

  void addedObject(LanguageTranslator *translator) override;
  void removedObject(LanguageTranslator *translator) override;
  void calculateAvailableLocales();

 private:
  static std::unique_ptr<LanguageManager> m_instance;

  QLocale m_current_locale;
  QList<QLocale> m_available_locales;
  QSet<LanguageTranslator *> m_translators;
};

}  // namespace egnite

#endif  // EGNITE_LANGUAGE_MANAGER_H
