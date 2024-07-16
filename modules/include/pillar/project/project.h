#ifndef PILLAR_PROJECT_H
#define PILLAR_PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/serializable.h>
/* -------------------------------------------------------------------------- */

namespace pillar {
class ProjectFormat;

class Project : public QObject, public qtils::Serializable {
  Q_OBJECT

 public:
  static std::unique_ptr<Project> create();
  static std::unique_ptr<Project> load(const QString &file_name,
                                       ProjectFormat *format = nullptr,
                                       QString *error = nullptr);

 public:
  ~Project() override;

  void setFileName(const QString &file_name);
  [[nodiscard]] QString getFileName() const;
  [[nodiscard]] QString getDisplayName() const;

  [[nodiscard]] ProjectFormat *getReaderFormat() const;
  [[nodiscard]] ProjectFormat *getWriterFormat() const;

  void setReaderFormat(ProjectFormat *format);
  void setWriterFormat(ProjectFormat *format);

  bool save(const QString &file_name, QString *error);

  void serialize(qtils::OArchive &archive) const override;
  void deserialize(qtils::IArchive &archive) override;

 Q_SIGNALS:
  void fileNameChanged(const QString &new_file_name,
                       const QString &old_file_name);
  void saved();

 protected:
  explicit Project(QObject *parent = nullptr);

 private:
  QString m_file_name;
  QString m_write_format;
  QString m_read_format;
};

}  // namespace pillar

#endif  // PILLAR_PROJECT_H
