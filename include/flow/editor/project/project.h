#ifndef FLOW_PROJECT_H
#define FLOW_PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
/* ------------------------------------ Api --------------------------------- */
#include "flow/api/project.h"
/* -------------------------------------------------------------------------- */

class Project : public api::IProject
{
  Q_OBJECT

public:
  static std::unique_ptr<api::IProject> create();
  static std::unique_ptr<api::IProject> load(const QString &file_name, api::IProjectFormat *format = nullptr, QString *error = nullptr);

public:
  ~Project() override;

  void setFileName(const QString &file_name) override;
  [[nodiscard]] QString getFileName() const override;
  [[nodiscard]] QString getDisplayName() const override;

  [[nodiscard]] api::IProjectFormat *getReaderFormat() const override;
  [[nodiscard]] api::IProjectFormat *getWriterFormat() const override;

  void setReaderFormat(api::IProjectFormat *format) override;
  void setWriterFormat(api::IProjectFormat *format) override;

  bool save(const QString &file_name, QString *error) override;

protected:
  explicit Project(QObject *parent = nullptr);

private:
  QString m_file_name;
  QString m_write_format;
  QString m_read_format;
};

#endif//FLOW_PROJECT_H
