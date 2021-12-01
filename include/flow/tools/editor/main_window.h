#ifndef FLOW_MAIN_WINDOW_H
#define FLOW_MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointer>
#include <QMainWindow>
#include <QStackedWidget>
/* -------------------------------------------------------------------------- */

namespace Ui { class MainWindow; }

class Document;

class AboutDialog;

class PreferencesManager;
class DocumentManager;
class LanguageManager;
class ActionManager;
class StyleManager;

class MainWindow final : public QMainWindow
{
Q_OBJECT

private:
  struct Preferences;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  [[nodiscard]] DocumentManager& getDocumentManager() const;
  [[nodiscard]] LanguageManager& getLanguageManager() const;
  [[nodiscard]] StyleManager& getStyleManager() const;
  [[nodiscard]] ActionManager& getActionManager() const;
  [[nodiscard]] PreferencesManager& getPreferencesManager() const;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void documentChanged(Document* document);

  bool confirmSave(Document* document);
  bool confirmAllSave();

  void updateActions();
  void updateWindowTitle();
  void updateViewsAndToolbarsMenu();
  void updateRecentDocumentFiles();
  void clearRecent();
  void openSettings();

  void newDocument();
  void openDocument();
  bool closeDocument(int index);
  bool closeDocument();
  bool saveDocument(Document* document);
  bool saveDocumentAs(Document* document);
  bool saveAllDocuments();

  void performCut();
  void performCopy();
  void performPaste();
  void performDelete();

  void openAbout();

private:
  void writeSettings();
  void readSettings();

  void registerMenus();
  void registerActions();
  void registerConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::MainWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;

  QPointer<AboutDialog> m_about_dialog;
};

#endif //FLOW_MAIN_WINDOW_H
