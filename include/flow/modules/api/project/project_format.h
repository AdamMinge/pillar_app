#ifndef FLOW_INTERFACE_PROJECT_FORMAT_H
#define FLOW_INTERFACE_PROJECT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/api/export.h"
#include "flow/modules/api/file_format.h"
/* -------------------------------------------------------------------------- */

namespace api::project
{

  class IProject;

  class API_API IProjectFormat : public IFileFormat
  {
    Q_OBJECT

  public:
    explicit IProjectFormat(QObject *parent = nullptr);
    ~IProjectFormat() override;

    virtual std::unique_ptr<IProject> load(const QString &file_name,
                                           QString *error) = 0;
    virtual bool save(const IProject &project, const QString &file_name,
                      QString *error) = 0;
  };

  class IReadableProjectFormat : public IProjectFormat
  {
    Q_OBJECT

  public:
    explicit IReadableProjectFormat(QObject *parent = nullptr);
    ~IReadableProjectFormat() override;

    bool save(const IProject &project, const QString &file_name,
              QString *error) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

  class IWritableProjectFormat : public IProjectFormat
  {
    Q_OBJECT

  public:
    explicit IWritableProjectFormat(QObject *parent = nullptr);
    ~IWritableProjectFormat() override;

    std::unique_ptr<IProject> load(const QString &file_name,
                                   QString *error) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

}// namespace api::project

#endif//FLOW_INTERFACE_PROJECT_FORMAT_H
