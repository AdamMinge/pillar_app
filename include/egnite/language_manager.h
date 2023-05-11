#ifndef EGNITE_LANGUAGE_MANAGER_H
#define EGNITE_LANGUAGE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLocale>
#include <QObject>
#include <QTranslator>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LIB_EGNITE_API LanguageManager : public QObject {
  Q_OBJECT

 public:
  static LanguageManager &getInstance();
  static void deleteInstance();

 public:
  ~LanguageManager() override;

  [[nodiscard]] QList<QLocale> getAvailableLanguages() const;
  [[nodiscard]] const QString &getTranslationsDir() const;
  [[nodiscard]] const QString &getTranslationsPrefix() const;

  [[nodiscard]] QLocale getCurrentLanguage() const;

 public Q_SLOTS:
  bool setLanguage(const QLocale &locale);
  void setTranslationsDir(const QString &translations_dir);
  void setTranslationsPrefix(const QString &translations_prefix);

 Q_SIGNALS:
  void languageChanged(const QLocale &locale);
  void translationsDirChanged(const QString &translations_dir);
  void translationsPrefixChanged(const QString &translations_prefix);

 private:
  explicit LanguageManager();

 private:
  static std::unique_ptr<LanguageManager> m_instance;

  QString m_translations_dir;
  QString m_translations_prefix;
  QScopedPointer<QTranslator> m_qt_translator;
  QScopedPointer<QTranslator> m_app_translator;
  QLocale m_current_locale;
};

}  // namespace egnite

#endif  // EGNITE_LANGUAGE_MANAGER_H
