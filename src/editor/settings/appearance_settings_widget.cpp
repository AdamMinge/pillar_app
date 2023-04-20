/* ----------------------------------- Local -------------------------------- */
#include "settings/appearance_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Flow --------------------------------- */
#include <flow/language_manager.h>
#include <flow/style_manager.h>
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

  auto &language_manager = flow::LanguageManager::getInstance();
  auto languages_str = QStringList{};
  for (auto &language : language_manager.getAvailableLanguages())
    languages_str << QLocale::languageToString(language.language());

  m_ui->m_language_combobox->addItems(languages_str);
  m_ui->m_language_combobox->setCurrentText(QLocale::languageToString(
      language_manager.getCurrentLanguage().language()));

  auto &style_manager = flow::StyleManager::getInstance();
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
}

void AppearanceSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void AppearanceSettingsWidget::languageChanged(const QString &language) {
  auto &language_manager = flow::LanguageManager::getInstance();
  language_manager.setLanguage(QLocale(language));
}

void AppearanceSettingsWidget::styleChanged(const QString &style) {
  auto &style_manager = flow::StyleManager::getInstance();
  style_manager.setStyle(style);
}

/* ---------------------- AppearanceSettingsWidgetFactory ------------------- */

AppearanceSettingsWidgetFactory::AppearanceSettingsWidgetFactory(
    QObject *parent)
    : flow::SettingsWidgetFactory(parent) {}

AppearanceSettingsWidgetFactory::~AppearanceSettingsWidgetFactory() = default;

std::unique_ptr<flow::SettingsWidget> AppearanceSettingsWidgetFactory::create()
    const {
  return std::make_unique<AppearanceSettingsWidget>();
}

QString AppearanceSettingsWidgetFactory::getParentObjectName() const {
  return QLatin1String("GeneralSettingsWidget");
}
