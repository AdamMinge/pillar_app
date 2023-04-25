#ifndef FLOW_DOCUMENT_OBJECT_H
#define FLOW_DOCUMENT_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
#include <QString>
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Object {
 public:
  explicit Object();
  virtual ~Object();

  void setName(const QString &name);
  [[nodiscard]] QString getName() const;

  void setPosition(const QPointF &position);
  [[nodiscard]] QPointF getPosition() const;

  void setProperties(const QVariantMap &properties);
  [[nodiscard]] const QVariantMap &getProperties() const;

 private:
  QString m_name;
  QPointF m_position;
  QVariantMap m_properties;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_H
