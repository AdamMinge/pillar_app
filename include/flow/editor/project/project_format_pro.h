#ifndef FLOW_PROJECT_FORMAT_PRO_H
#define FLOW_PROJECT_FORMAT_PRO_H

/* ------------------------------------ Api --------------------------------- */
#include "flow/api/project/project_format.h"
/* -------------------------------------------------------------------------- */

class ProjectFormatPro : public api::project::IProjectFormat
{
  Q_OBJECT

public:
  explicit ProjectFormatPro(QObject *parent = nullptr);
  ~ProjectFormatPro() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<api::project::IProject> load(const QString &file_name,
                                               QString *error) override;
  bool save(const api::project::IProject &project, const QString &file_name,
            QString *error) override;
};

#endif//FLOW_PROJECT_FORMAT_PRO_H
