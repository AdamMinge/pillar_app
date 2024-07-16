/* ----------------------------------- Local -------------------------------- */
#include "pillar/language_translator.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QDirIterator>
#include <QLibraryInfo>
/* -------------------------------------------------------------------------- */

namespace pillar {

/* ----------------------------- LanguageTranslator ------------------------- */

LanguageTranslator::LanguageTranslator(QObject *parent) : QObject(parent) {}

LanguageTranslator::~LanguageTranslator() = default;

/* --------------------------- BaseLanguageTranslator ----------------------- */

BaseLanguageTranslator::BaseLanguageTranslator(const QString &path,
                                               QObject *parent)
    : BaseLanguageTranslator(path, {}, parent) {}

BaseLanguageTranslator::BaseLanguageTranslator(const QString &path,
                                               const QString &prefix,
                                               QObject *parent)
    : LanguageTranslator(parent), m_translator(nullptr) {
  init(path, prefix);
}

BaseLanguageTranslator::~BaseLanguageTranslator() {
  if (QApplication::instance() && m_translator)
    QApplication::removeTranslator(m_translator.get());
}

QList<QLocale> BaseLanguageTranslator::getAvailableLanguages() const {
  auto languages = QList<QLocale>{};

  for (auto iter = m_bcp47_to_factory.begin(); iter != m_bcp47_to_factory.end();
       ++iter) {
    languages.append(QLocale(iter.key()));
  }

  return languages;
}

QLocale BaseLanguageTranslator::getCurrentLanguage() const {
  return m_current_locale;
}

bool BaseLanguageTranslator::setLanguage(const QLocale &locale) {
  if (m_current_locale == locale) return true;

  const auto bcp47_name = locale.bcp47Name();
  if (!m_bcp47_to_factory.contains(bcp47_name)) return false;

  auto new_translator = m_bcp47_to_factory[bcp47_name]();
  if (!new_translator) return false;

  if (m_translator) QApplication::removeTranslator(m_translator.get());
  m_translator = std::move(new_translator);
  QApplication::installTranslator(m_translator.get());

  m_current_locale = locale;
  Q_EMIT languageChanged(locale);
  return true;
}

void BaseLanguageTranslator::init(const QString &path, const QString &prefix) {
  const auto filters = QStringList{prefix + QLatin1String("*.qm")};
  QDirIterator iterator(path, filters, QDir::Files | QDir::Readable);

  while (iterator.hasNext()) {
    iterator.next();
    const auto dir = iterator.path();
    const auto base_name = iterator.fileInfo().completeBaseName();
    const auto suffix_index = base_name.lastIndexOf("_");
    const auto filename = base_name.mid(0, suffix_index);
    const auto bcp47_name = base_name.mid(suffix_index + 1);

    m_bcp47_to_factory.insert(
        bcp47_name,
        [dir, filename, bcp47_name]() -> std::unique_ptr<QTranslator> {
          auto translator = std::make_unique<QTranslator>();
          if (!translator->load(
                  QLatin1String("%1_%2").arg(filename, bcp47_name), dir)) {
            return nullptr;
          }

          return translator;
        });
  }
}

}  // namespace pillar
