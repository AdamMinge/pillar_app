#ifndef FLOW_PROJECT_FORMAT_PRO_H
#define FLOW_PROJECT_FORMAT_PRO_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/project/project_format.h>
/* -------------------------------------------------------------------------- */

class ProjectFormatPro : public flow::ProjectFormat {
  Q_OBJECT
  Q_INTERFACES(flow::ProjectFormat)

 public:
  explicit ProjectFormatPro(QObject *parent = nullptr);
  ~ProjectFormatPro() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<flow::Project> load(const QString &file_name,
                                      QString *error) override;
  bool save(const flow::Project &project, const QString &file_name,
            QString *error) override;
};

#endif  // FLOW_PROJECT_FORMAT_PRO_H
