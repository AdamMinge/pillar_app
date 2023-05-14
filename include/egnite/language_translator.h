#ifndef EGNITE_LANGUAGE_TRANSLATOR_H
#define EGNITE_LANGUAGE_TRANSLATOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLocale>
#include <QObject>
#include <QTranslator>
/* ---------------------------------- Standard ------------------------------ */
#include <functional>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

/* ----------------------------- LanguageTranslator ------------------------- */

class LIB_EGNITE_API LanguageTranslator : public QObject {
  Q_OBJECT

 public:
  LanguageTranslator(QObject *parent = nullptr);
  ~LanguageTranslator() override;

  [[nodiscard]] virtual QList<QLocale> getAvailableLanguages() const = 0;
  [[nodiscard]] virtual QLocale getCurrentLanguage() const = 0;

 public Q_SLOTS:
  virtual bool setLanguage(const QLocale &locale) = 0;

 Q_SIGNALS:
  void languageChanged(const QLocale &locale);
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::LanguageTranslator, "org.egnite.LanguageTranslator")

namespace egnite {

/* --------------------------- BaseLanguageTranslator ----------------------- */

class LIB_EGNITE_API BaseLanguageTranslator : public LanguageTranslator {
  Q_OBJECT
  Q_INTERFACES(egnite::LanguageTranslator)

  using TranslationFactory = std::function<std::unique_ptr<QTranslator>()>;

 public:
  BaseLanguageTranslator(const QString &path, QObject *parent = nullptr);
  BaseLanguageTranslator(const QString &path, const QString &prefix,
                         QObject *parent = nullptr);
  ~BaseLanguageTranslator() override;

  [[nodiscard]] QList<QLocale> getAvailableLanguages() const override;
  [[nodiscard]] QLocale getCurrentLanguage() const override;

  bool setLanguage(const QLocale &locale) override;

 private:
  void init(const QString &path, const QString &prefix);

 private:
  std::unique_ptr<QTranslator> m_translator;
  QMap<QString, TranslationFactory> m_bcp47_to_factory;
  QLocale m_current_locale;
};

}  // namespace egnite

#endif  // EGNITE_LANGUAGE_TRANSLATOR_H
