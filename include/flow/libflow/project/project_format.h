#ifndef FLOW_PROJECT_FORMAT_H
#define FLOW_PROJECT_FORMAT_H

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
    Q_INTERFACES(flow::FileFormat)

  public:
    explicit ProjectFormat(QObject *parent = nullptr);
    ~ProjectFormat() override;

    virtual std::unique_ptr<Project>
    load(const QString &file_name, QString *error) = 0;
    virtual bool
    save(const Project &project, const QString &file_name, QString *error) = 0;
  };

}// namespace flow::project

Q_DECLARE_INTERFACE(flow::project::ProjectFormat, "org.flow.ProjectFormat")

namespace flow::project
{

  class ReadableProjectFormat : public ProjectFormat
  {
    Q_OBJECT
    Q_INTERFACES(flow::project::ProjectFormat)

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
    Q_INTERFACES(flow::project::ProjectFormat)

  public:
    explicit WritableProjectFormat(QObject *parent = nullptr);
    ~WritableProjectFormat() override;

    std::unique_ptr<Project>
    load(const QString &file_name, QString *error) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

}// namespace flow::project

Q_DECLARE_INTERFACE(
  flow::project::ReadableProjectFormat, "org.flow.ReadableProjectFormat")
Q_DECLARE_INTERFACE(
  flow::project::WritableProjectFormat, "org.flow.WritableProjectFormat")

#endif//FLOW_PROJECT_FORMAT_H
