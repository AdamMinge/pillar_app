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
    enum class Type;

  public:
    explicit Pin(std::unique_ptr<NodeData> data, QString caption = {});
    ~Pin() override;

    [[nodiscard]] const NodeData &getData() const;
    [[nodiscard]] QString getCaption() const;

  public Q_SLOTS:
    void setCaption(const QString &caption);
    void setData(const flow::node::NodeData &data);

  Q_SIGNALS:
    void captionChanged(const QString &caption);
    void dataChanged(const flow::node::NodeData &data);

  private:
    std::unique_ptr<NodeData> m_data;
    QString m_caption;
  };

  enum class Pin::Type
  {
    In,
    Out
  };

}// namespace flow::node

#endif//FLOW_PIN_H
