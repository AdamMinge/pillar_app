#ifndef PROJECT_FORMAT_PRO_H
#define PROJECT_FORMAT_PRO_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/project/project_format.h>
/* -------------------------------------------------------------------------- */

class ProjectFormatPro : public pillar::ProjectFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::ProjectFormat)

 public:
  explicit ProjectFormatPro(QObject *parent = nullptr);
  ~ProjectFormatPro() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<pillar::Project> load(const QString &file_name,
                                        QString *error) override;
  bool save(const pillar::Project &project, const QString &file_name,
            QString *error) override;
};

#endif  // PROJECT_FORMAT_PRO_H
