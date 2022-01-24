#ifndef FLOW_PROJECT_WRITER_H
#define FLOW_PROJECT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

namespace api
{
  class IProject;
}

class ProjectWriter
{
  class ProjectWriterImpl;

public:
  explicit ProjectWriter();
  ~ProjectWriter();

  void write(const api::IProject &project, QIODevice &device);
  bool write(const api::IProject &project, const QString &file_name);

private:
  std::unique_ptr<ProjectWriterImpl> m_impl;
};

#endif//FLOW_PROJECT_WRITER_H
