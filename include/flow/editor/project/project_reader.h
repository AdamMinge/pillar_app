#ifndef FLOW_PROJECT_READER_H
#define FLOW_PROJECT_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class Project;

class ProjectReader
{
  class ProjectReaderImpl;

public:
  explicit ProjectReader();
  ~ProjectReader();

  std::unique_ptr<Project> read(QIODevice &device, QString *error = nullptr);
  std::unique_ptr<Project> read(const QString &file_name, QString *error = nullptr);

private:
  std::unique_ptr<ProjectReaderImpl> m_impl;
};

#endif//FLOW_PROJECT_READER_H
