#ifndef FLOW_PROJECT_FORMAT_PRO_H
#define FLOW_PROJECT_FORMAT_PRO_H

/* ------------------------------------ Api --------------------------------- */
#include "flow/api/project_format.h"
/* -------------------------------------------------------------------------- */

class ProjectFormatPro : public api::IProjectFormat
{
  Q_OBJECT

public:
  explicit ProjectFormatPro(QObject *parent = nullptr);
  ~ProjectFormatPro() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<api::IProject> load(const QString &file_name) override;
  bool save(const api::IProject &project) override;
};

#endif//FLOW_PROJECT_FORMAT_PRO_H
