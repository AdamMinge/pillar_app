#ifndef FLOW_PIN_H
#define FLOW_PIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class NodeData;

  class LIB_FLOW_API Pin : public QObject
  {
    Q_OBJECT

  public:
    enum class Policy;
    enum class Type;

  public:
    explicit Pin(
      std::unique_ptr<NodeData> data, Policy policy, QString caption = {});
    ~Pin() override;

    [[nodiscard]] const NodeData &getData() const;

  public Q_SLOTS:
    void setCaption(const QString &caption);
    void setData(const NodeData &data);
    void setPolicy(Pin::Policy policy);

  Q_SIGNALS:
    void captionChanged(const QString &caption);
    void dataChanged(const NodeData &data);
    void policyChanged(Pin::Policy policy);

  private:
    std::unique_ptr<NodeData> m_data;
    Policy m_policy;
    QString m_caption;
  };

  enum class Pin::Policy
  {
    ConnectionOne,
    ConnectionMany
  };

  enum class Pin::Type
  {
    In,
    Out
  };

}// namespace flow::node

#endif//FLOW_PIN_H
