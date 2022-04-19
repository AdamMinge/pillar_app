#ifndef FLOW_PROJECT_H
#define FLOW_PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
/* -------------------------------------------------------------------------- */

namespace flow::project
{
  class ProjectFormat;

  class Project : public QObject
  {
    Q_OBJECT

  public:
    static std::unique_ptr<Project> create();
    static std::unique_ptr<Project> load(
      const QString &file_name, ProjectFormat *format = nullptr,
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

  Q_SIGNALS:
    void
    fileNameChanged(const QString &new_file_name, const QString &old_file_name);
    void saved();

  protected:
    explicit Project(QObject *parent = nullptr);

  private:
    QString m_file_name;
    QString m_write_format;
    QString m_read_format;
  };

}// namespace flow::project

#endif//FLOW_PROJECT_H
