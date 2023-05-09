#ifndef FLOW_DOCUMENT_FACTORY_H
#define FLOW_DOCUMENT_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupFactory;

class FLOW_DOCUMENT_API Factory : public QObject {
  Q_OBJECT

  friend GroupFactory;

 public:
  enum class Type {
    GroupFactory,
    NodeFactory,
  };

 public:
  explicit Factory(Type type, QString name);
  ~Factory() override;

  [[nodiscard]] Type getType() const;

  [[nodiscard]] const QString &getName() const;
  [[nodiscard]] GroupFactory *getParent() const;

 protected:
  void setParent(GroupFactory *parent);

 private:
  Type m_type;
  QString m_name;
  GroupFactory *m_parent;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FACTORY_H