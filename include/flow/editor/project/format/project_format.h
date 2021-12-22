#ifndef FLOW_PROJECT_FORMAT_H
#define FLOW_PROJECT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/file_format.h"
/* -------------------------------------------------------------------------- */

class Project;

class ProjectFormat : public FileFormat
{
  Q_OBJECT

public:
  explicit ProjectFormat(QObject *parent = nullptr);
  ~ProjectFormat() override;

  virtual std::unique_ptr<Project> load(const QString &file_name) = 0;
  virtual bool save(const Project &project) = 0;
};

class ReadableProjectFormat : public ProjectFormat
{
  Q_OBJECT

public:
  explicit ReadableProjectFormat(QObject *parent = nullptr);
  ~ReadableProjectFormat() override;

  bool save(const Project &project) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableProjectFormat : public ProjectFormat
{
  Q_OBJECT

public:
  explicit WritableProjectFormat(QObject *parent = nullptr);
  ~WritableProjectFormat() override;

  std::unique_ptr<Project> load(const QString &file_name) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

#endif//FLOW_PROJECT_FORMAT_H
