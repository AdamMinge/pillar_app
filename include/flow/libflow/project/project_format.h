#ifndef FLOW_INTERFACE_PROJECT_FORMAT_H
#define FLOW_INTERFACE_PROJECT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/file_format.h"
/* -------------------------------------------------------------------------- */

namespace flow::project
{

  class Project;

  class LIB_FLOW_API ProjectFormat : public FileFormat
  {
    Q_OBJECT

  public:
    explicit ProjectFormat(QObject *parent = nullptr);
    ~ProjectFormat() override;

    virtual std::unique_ptr<Project>
    load(const QString &file_name, QString *error) = 0;
    virtual bool
    save(const Project &project, const QString &file_name, QString *error) = 0;
  };

  class ReadableProjectFormat : public ProjectFormat
  {
    Q_OBJECT

  public:
    explicit ReadableProjectFormat(QObject *parent = nullptr);
    ~ReadableProjectFormat() override;

    bool save(const Project &project, const QString &file_name, QString *error)
      override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

  class WritableProjectFormat : public ProjectFormat
  {
    Q_OBJECT

  public:
    explicit WritableProjectFormat(QObject *parent = nullptr);
    ~WritableProjectFormat() override;

    std::unique_ptr<Project>
    load(const QString &file_name, QString *error) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

}// namespace flow::project

#endif//FLOW_INTERFACE_PROJECT_FORMAT_H
