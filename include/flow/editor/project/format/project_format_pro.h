#ifndef FLOW_PROJECT_FORMAT_PRO_H
#define FLOW_PROJECT_FORMAT_PRO_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/format/project_format.h"
/* -------------------------------------------------------------------------- */

class ProjectFormatPro : public ProjectFormat
{
  Q_OBJECT

public:
  explicit ProjectFormatPro(QObject *parent = nullptr);
  ~ProjectFormatPro() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<Project> load(const QString &file_name) override;
  bool save(const Project &project) override;
};

#endif//FLOW_PROJECT_FORMAT_PRO_H
