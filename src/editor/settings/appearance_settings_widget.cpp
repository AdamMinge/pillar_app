/* ----------------------------------- Local -------------------------------- */
#include "settings/appearance_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/language_manager.h>
#include <egnite/style_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_appearance_settings_widget.h"
/* -------------------------------------------------------------------------- */

/* ------------------------- AppearanceSettingsWidget ----------------------- */

AppearanceSettingsWidget::AppearanceSettingsWidget(QWidget *parent)
    : SettingsWidget(parent), m_ui(new Ui::AppearanceSettingsWidget()) {
  initUi();
  initConnections();

  retranslateUi();
}

AppearanceSettingsWidget::~AppearanceSettingsWidget() = default;

void AppearanceSettingsWidget::changeEvent(QEvent *event) {
  QWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void AppearanceSettingsWidget::initUi() {
  m_ui->setupUi(this);

  auto &language_manager = egnite::LanguageManager::getInstance();
  availableLanguagesChanged(language_manager.getAvailableLanguages());

  auto &style_manager = egnite::StyleManager::getInstance();
  auto styles = style_manager.getAvailableStyles();

  m_ui->m_theme_combobox->addItems(styles);
  m_ui->m_theme_combobox->setCurrentIndex(m_ui->m_theme_combobox->findText(
      style_manager.getCurrentStyle(), Qt::MatchFixedString));
}

void AppearanceSettingsWidget::initConnections() {
  connect(m_ui->m_language_combobox, &QComboBox::currentTextChanged, this,
          &AppearanceSettingsWidget::languageChanged);

  connect(m_ui->m_theme_combobox, &QComboBox::currentTextChanged, this,
          &AppearanceSettingsWidget::styleChanged);

  auto &language_manager = egnite::LanguageManager::getInstance();
  connect(&language_manager,
          &egnite::LanguageManager::availableLanguagesChanged, this,
          &AppearanceSettingsWidget::availableLanguagesChanged);
}

void AppearanceSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void AppearanceSettingsWidget::languageChanged(const QString &language) {
  auto &language_manager = egnite::LanguageManager::getInstance();
  language_manager.setLanguage(QLocale(language));
}

void AppearanceSettingsWidget::styleChanged(const QString &style) {
  auto &style_manager = egnite::StyleManager::getInstance();
  style_manager.setStyle(style);
}

void AppearanceSettingsWidget::availableLanguagesChanged(
    const QList<QLocale> &locales) {
  auto &language_manager = egnite::LanguageManager::getInstance();
  auto languages_str = QStringList{};
  for (const auto &language : language_manager.getAvailableLanguages())
    languages_str << QLocale::languageToString(language.language());

  m_ui->m_language_combobox->clear();
  m_ui->m_language_combobox->addItems(languages_str);
  m_ui->m_language_combobox->setCurrentText(QLocale::languageToString(
      language_manager.getCurrentLanguage().language()));
}

/* ---------------------- AppearanceSettingsWidgetFactory ------------------- */

AppearanceSettingsWidgetFactory::AppearanceSettingsWidgetFactory(
    QObject *parent)
    : egnite::SettingsWidgetFactory(parent) {}

AppearanceSettingsWidgetFactory::~AppearanceSettingsWidgetFactory() = default;

std::unique_ptr<egnite::SettingsWidget>
AppearanceSettingsWidgetFactory::create() const {
  return std::make_unique<AppearanceSettingsWidget>();
}

QString AppearanceSettingsWidgetFactory::getParentObjectName() const {
  return QLatin1String("GeneralSettingsWidget");
}
