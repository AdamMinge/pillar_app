#ifndef FLOW_PIN_H
#define FLOW_PIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  namespace data
  {
    class NodeData;
  }

  class NODE_API Pin : public QObject
  {
    Q_OBJECT

  public:
    enum class Policy;
    enum class Type;

  public:
    explicit Pin(
      std::unique_ptr<data::NodeData> data, Policy policy,
      QString caption = {});
    ~Pin() override;

    [[nodiscard]] const data::NodeData &getData() const;

  public Q_SLOTS:
    void setCaption(const QString &caption);
    void setData(const data::NodeData &data);
    void setPolicy(Pin::Policy policy);

  Q_SIGNALS:
    void captionChanged(const QString &caption);
    void dataChanged(const data::NodeData &data);
    void policyChanged(Pin::Policy policy);

  private:
    std::unique_ptr<data::NodeData> m_data;
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
