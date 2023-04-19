#ifndef FLOW_OBJECT_H
#define FLOW_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QPointF>
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

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

}  // namespace plugin::flow_document

#endif  // FLOW_OBJECT_H
