/* ----------------------------------- Local -------------------------------- */
#include "about_dialog.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_about_dialog.h"
/* -------------------------------------------------------------------------- */

AboutDialog::AboutDialog(QWidget *parent)
    : qtils::QtDialogWithUrlLinks<AboutDialog>(parent),
      m_ui(new Ui::AboutDialog()) {
  m_ui->setupUi(this);

  retranslateUi();
}

AboutDialog::~AboutDialog() = default;

void AboutDialog::changeEvent(QEvent *event) {
  QDialog::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void AboutDialog::retranslateUi() {
  m_ui->retranslateUi(this);

  setWindowTitle(tr("About"));

  const auto link_color = palette().color(QPalette::Link).name(QColor::HexRgb);
  const auto button_text_color =
      palette().color(QPalette::ButtonText).name(QColor::HexRgb);

  auto about_text =
      QString{
          "<html>"
          "<head/>"
          "<body>"
          "<p align=\"center\"><span style=\" font-size:48pt; "
          "font-weight:700;\">Egnite</span></p>"
          "<p align=\"center\"><span style=\" color:#%1;\">%2</span></p>"
          "<p align=\"center\"><span style=\" font-size:12pt;\">%3</span></p>"
          "<p align=\"center\"><span style=\" font-size:12pt;\">%4 </span><a "
          "href=\"%5\"><span style=\" font-size:12pt; "
          "text-decoration: underline; color:#%6;\">%7</span></a> <span "
          "style=\" font-size:12pt;\"><br/> %8</span></p>"
          "<p align=\"center\"><span style=\" "
          "color:#%1;\">%9</span><br/></p>"
          "</body>"
          "</html>"}
          .arg(button_text_color,
               tr("Version %1")
                   .arg(QApplication::instance()->applicationVersion()),
               tr("This Project is open source and <br/> contributions are "
                  "welcomed."),
               tr("Visit"), tr("https://github.com/AdamMinge/flow_app"),
               link_color, tr("GitHub/AdamMinge/flow_app"),
               tr("for more information or to report a bug <br> or to suggest "
                  "a new "
                  "feature."),
               tr("Copyright © 2023 Adam Minge. All rights reserved."));

  m_ui->m_about_label->setText(about_text);
}