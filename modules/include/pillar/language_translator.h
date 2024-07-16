#ifndef PILLAR_LANGUAGE_TRANSLATOR_H
#define PILLAR_LANGUAGE_TRANSLATOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLocale>
#include <QObject>
#include <QTranslator>
/* ---------------------------------- Standard ------------------------------ */
#include <functional>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

/* ----------------------------- LanguageTranslator ------------------------- */

class LIB_PILLAR_API LanguageTranslator : public QObject {
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

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::LanguageTranslator, "org.pillar.LanguageTranslator")

namespace pillar {

/* --------------------------- BaseLanguageTranslator ----------------------- */

class LIB_PILLAR_API BaseLanguageTranslator : public LanguageTranslator {
  Q_OBJECT
  Q_INTERFACES(pillar::LanguageTranslator)

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

}  // namespace pillar

#endif  // PILLAR_LANGUAGE_TRANSLATOR_H
