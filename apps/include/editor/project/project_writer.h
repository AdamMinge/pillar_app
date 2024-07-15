#ifndef PROJECT_WRITER_H
#define PROJECT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnite {
class Project;
}

class ProjectWriter {
  class ProjectWriterImpl;

 public:
  explicit ProjectWriter();
  ~ProjectWriter();

  void write(const egnite::Project &project, QIODevice &device);
  bool write(const egnite::Project &project, const QString &file_name,
             QString *error = nullptr);

 private:
  std::unique_ptr<ProjectWriterImpl> m_impl;
};

#endif  // PROJECT_WRITER_H
