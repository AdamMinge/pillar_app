#ifndef FLOW_NAME_AND_PATH_FILLER_H
#define FLOW_NAME_AND_PATH_FILLER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/widget/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class QtNameAndPathFiller;
}

namespace utils
{

  class QtNameAndPathFiller : public QWidget
  {
    Q_OBJECT

  public:
    explicit QtNameAndPathFiller(QWidget *parent = nullptr);
    ~QtNameAndPathFiller() override;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QString getPath() const;

    [[nodiscard]] bool isValid() const;

  Q_SIGNALS:
    void nameChanged(const QString &name);
    void pathChanged(const QString &name);
    bool validStateChanged(bool isValid);

  protected:
    void changeEvent(QEvent *event) override;

  private Q_SLOTS:
    void nameChanged();
    void pathChanged();

  private:
    void initUi();
    void initConnections();

    void retranslateUi();

  private:
    QScopedPointer<Ui::QtNameAndPathFiller> m_ui;
  };

}// namespace utils

#endif//FLOW_NAME_AND_PATH_FILLER_H
