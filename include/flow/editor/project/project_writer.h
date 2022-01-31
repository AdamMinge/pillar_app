#ifndef FLOW_PROJECT_WRITER_H
#define FLOW_PROJECT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class Project;

class ProjectWriter
{
  class ProjectWriterImpl;

public:
  explicit ProjectWriter();
  ~ProjectWriter();

  void write(const Project &project, QIODevice &device);
  bool write(const Project &project, const QString &file_name,
             QString *error = nullptr);

private:
  std::unique_ptr<ProjectWriterImpl> m_impl;
};

#endif//FLOW_PROJECT_WRITER_H
