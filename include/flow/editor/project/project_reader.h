#ifndef FLOW_PROJECT_READER_H
#define FLOW_PROJECT_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

namespace api
{
  class IProject;
}

class ProjectReader
{
  class ProjectReaderImpl;

public:
  explicit ProjectReader();
  ~ProjectReader();

  std::unique_ptr<api::IProject> read(QIODevice &device);
  std::unique_ptr<api::IProject> read(const QString &file_name);

private:
  std::unique_ptr<ProjectReaderImpl> m_impl;
};

#endif//FLOW_PROJECT_READER_H
