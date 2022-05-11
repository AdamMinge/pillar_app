#ifndef FLOW_OBJECT_H
#define FLOW_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QPointF>
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{

  class LIB_FLOW_API Object
  {
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

}// namespace flow

#endif//FLOW_OBJECT_H
