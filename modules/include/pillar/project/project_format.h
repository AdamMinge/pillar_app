#ifndef PILLAR_PROJECT_FORMAT_H
#define PILLAR_PROJECT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
#include "pillar/file_format.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class Project;

class LIB_PILLAR_API ProjectFormat : public FileFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::FileFormat)

 public:
  explicit ProjectFormat(QObject *parent = nullptr);
  ~ProjectFormat() override;

  virtual std::unique_ptr<Project> load(const QString &file_name,
                                        QString *error) = 0;
  virtual bool save(const Project &project, const QString &file_name,
                    QString *error) = 0;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::ProjectFormat, "org.pillar.ProjectFormat")

namespace pillar {

class ReadableProjectFormat : public ProjectFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::ProjectFormat)

 public:
  explicit ReadableProjectFormat(QObject *parent = nullptr);
  ~ReadableProjectFormat() override;

  bool save(const Project &project, const QString &file_name,
            QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableProjectFormat : public ProjectFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::ProjectFormat)

 public:
  explicit WritableProjectFormat(QObject *parent = nullptr);
  ~WritableProjectFormat() override;

  std::unique_ptr<Project> load(const QString &file_name,
                                QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::ReadableProjectFormat,
                    "org.pillar.ReadableProjectFormat")
Q_DECLARE_INTERFACE(pillar::WritableProjectFormat,
                    "org.pillar.WritableProjectFormat")

#endif  // PILLAR_PROJECT_FORMAT_H
