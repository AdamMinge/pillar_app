#ifndef FLOW_LANGUAGE_MANAGER_H
#define FLOW_LANGUAGE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLocale>
#include <QObject>
#include <QScopedPointer>
#include <QTranslator>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_API LanguageManager : public QObject {
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
  static QScopedPointer<LanguageManager> m_instance;

  QString m_translations_dir;
  QString m_translations_prefix;
  QScopedPointer<QTranslator> m_qt_translator;
  QScopedPointer<QTranslator> m_app_translator;
  QLocale m_current_locale;
};

}  // namespace flow

#endif  // FLOW_LANGUAGE_MANAGER_H
