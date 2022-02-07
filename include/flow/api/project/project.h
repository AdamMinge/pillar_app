#ifndef FLOW_INTERFACE_PROJECT_H
#define FLOW_INTERFACE_PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
/* -------------------------------------------------------------------------- */

namespace api::project
{

  class IProjectFormat;

  class API_API IProject : public QObject
  {
    Q_OBJECT

  public:
    ~IProject() override;

    virtual void setFileName(const QString &file_name) = 0;
    [[nodiscard]] virtual QString getFileName() const = 0;
    [[nodiscard]] virtual QString getDisplayName() const = 0;

    [[nodiscard]] virtual IProjectFormat *getReaderFormat() const = 0;
    [[nodiscard]] virtual IProjectFormat *getWriterFormat() const = 0;

    virtual void setReaderFormat(IProjectFormat *format) = 0;
    virtual void setWriterFormat(IProjectFormat *format) = 0;

    virtual bool save(const QString &file_name, QString *error) = 0;

  Q_SIGNALS:
    void fileNameChanged(const QString &new_file_name,
                         const QString &old_file_name);
    void saved();

  protected:
    explicit IProject(QObject *parent = nullptr);
  };

}// namespace api::project

#endif//FLOW_INTERFACE_PROJECT_H
