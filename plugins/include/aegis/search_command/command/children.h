#ifndef AEGIS_SEARCH_COMMAND_CHILDREN_H
#define AEGIS_SEARCH_COMMAND_CHILDREN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QTimer>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- ObjectChildrenMessage ----------------------- */

struct LIB_AEGIS_SEARCH_COMMAND_API ObjectChildrenMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QString object MEMBER object)
  Q_PROPERTY(QStringList children MEMBER children)

  [[nodiscard]] bool operator==(const ObjectChildrenMessage& other) const;
  [[nodiscard]] bool operator!=(const ObjectChildrenMessage& other) const;

  QString object;
  QStringList children;
};

/* --------------------------- ObjectsChildrenMessage ----------------------- */

struct LIB_AEGIS_SEARCH_COMMAND_API ObjectsChildrenMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QList<ObjectChildrenMessage> objects MEMBER objects)

  QList<ObjectChildrenMessage> objects;
};

/* ------------------------------- ChildrenFinder --------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ChildrenFinder {
 public:
  using Result = Response<ObjectsChildrenMessage>;

 public:
  explicit ChildrenFinder();
  ~ChildrenFinder();

  Result find(const QString& id);

 private:
  [[nodiscard]] QStringList getChildren(const QObject* object) const;
};

/* ------------------------------ ChildrenCommand --------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ChildrenCommand : public Command {
 public:
  explicit ChildrenCommand();
  ~ChildrenCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  ChildrenFinder m_finder;
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_CHILDREN_H