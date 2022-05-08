#ifndef FLOW_OBJECT_H
#define FLOW_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QPointF>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{

  class LIB_FLOW_API Object : public QObject
  {
    Q_OBJECT

  public:
    explicit Object();
    ~Object() override;

    void setPosition(const QPointF &position);
    [[nodiscard]] QPointF getPosition() const;

  Q_SIGNALS:
    void positionChanged(const QPointF &position);

  private:
    QPointF m_position;
  };

}// namespace flow

#endif//FLOW_OBJECT_H
