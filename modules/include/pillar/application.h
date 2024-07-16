#ifndef PILLAR_APPLICATION_H
#define PILLAR_APPLICATION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

/* -------------------------------- Application ----------------------------- */

class LIB_PILLAR_API Application : public QApplication {
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

}  // namespace pillar

#endif  // PILLAR_APPLICATION_H
