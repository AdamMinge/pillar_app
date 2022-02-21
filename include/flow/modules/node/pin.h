#ifndef FLOW_PIN_H
#define FLOW_PIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class NodeData;

  class NODE_API Pin : public QObject
  {
    Q_OBJECT

  public:
    enum class Policy;
    enum class Type;

  public:
    explicit Pin(
      std::unique_ptr<node::NodeData> data, Policy policy,
      QString caption = {});
    ~Pin() override;

    [[nodiscard]] const node::NodeData &getData() const;

  public Q_SLOTS:
    void setCaption(const QString &caption);
    void setData(const node::NodeData &data);
    void setPolicy(node::Pin::Policy policy);

  Q_SIGNALS:
    void captionChanged(const QString &caption);
    void dataChanged(const node::NodeData &data);
    void policyChanged(node::Pin::Policy policy);

  private:
    std::unique_ptr<node::NodeData> m_data;
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

}// namespace node

#endif//FLOW_PIN_H
