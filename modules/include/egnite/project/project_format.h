#ifndef EGNITE_PROJECT_FORMAT_H
#define EGNITE_PROJECT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
#include "egnite/file_format.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class Project;

class LIB_EGNITE_API ProjectFormat : public FileFormat {
  Q_OBJECT
  Q_INTERFACES(egnite::FileFormat)

 public:
  explicit ProjectFormat(QObject *parent = nullptr);
  ~ProjectFormat() override;

  virtual std::unique_ptr<Project> load(const QString &file_name,
                                        QString *error) = 0;
  virtual bool save(const Project &project, const QString &file_name,
                    QString *error) = 0;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::ProjectFormat, "org.egnite.ProjectFormat")

namespace egnite {

class ReadableProjectFormat : public ProjectFormat {
  Q_OBJECT
  Q_INTERFACES(egnite::ProjectFormat)

 public:
  explicit ReadableProjectFormat(QObject *parent = nullptr);
  ~ReadableProjectFormat() override;

  bool save(const Project &project, const QString &file_name,
            QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableProjectFormat : public ProjectFormat {
  Q_OBJECT
  Q_INTERFACES(egnite::ProjectFormat)

 public:
  explicit WritableProjectFormat(QObject *parent = nullptr);
  ~WritableProjectFormat() override;

  std::unique_ptr<Project> load(const QString &file_name,
                                QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::ReadableProjectFormat,
                    "org.egnite.ReadableProjectFormat")
Q_DECLARE_INTERFACE(egnite::WritableProjectFormat,
                    "org.egnite.WritableProjectFormat")

#endif  // EGNITE_PROJECT_FORMAT_H
