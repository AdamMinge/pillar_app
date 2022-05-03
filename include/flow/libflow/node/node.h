#ifndef FLOW_NODE_H
#define FLOW_NODE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QPointF>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class LIB_FLOW_API Node : public QObject
  {
    Q_OBJECT

  public:
    explicit Node();
    ~Node() override;

    [[nodiscard]] unsigned getPinsCounts(Pin::Type type) const;

    [[nodiscard]] const Pin &getPin(Pin::Type type, unsigned index) const;
    [[nodiscard]] Pin &getPin(Pin::Type type, unsigned index);

    void insertPin(Pin::Type type, std::unique_ptr<Pin> pin, int index);
    void removePin(Pin::Type type, int index);

    void setPosition(const QPointF &position);
    [[nodiscard]] QPointF getPosition() const;

  protected Q_SLOTS:
    virtual void compute() = 0;

  private:
    [[nodiscard]] std::vector<std::unique_ptr<Pin>> &getPins(Pin::Type type);
    [[nodiscard]] const std::vector<std::unique_ptr<Pin>> &
    getPins(Pin::Type type) const;

  private:
    std::vector<std::unique_ptr<Pin>> m_out_pins;
    std::vector<std::unique_ptr<Pin>> m_in_pins;
    QPointF m_position;
  };

}// namespace flow::node

#endif//FLOW_NODE_H
