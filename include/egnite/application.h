#ifndef EGNITE_APPLICATION_H
#define EGNITE_APPLICATION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

/* -------------------------------- Application ----------------------------- */

class LIB_EGNITE_API Application : public QApplication {
  Q_OBJECT

 private:
  struct Preferences;

 public:
  Application(int &argc, char **argv);
  ~Application() override;

  bool event(QEvent *event) override;

 private:
  void parseCommandLine();

  void writeSettings();
  void writePlugins();
  void writeLanguage();
  void writeStyle();
  void writeShortcuts();

  void readSettings();
  void readPlugins();
  void readLanguage();
  void readStyle();
  void readShortcuts();

 private:
  QScopedPointer<Preferences> m_preferences;
};

}  // namespace egnite

#endif  // EGNITE_APPLICATION_H
