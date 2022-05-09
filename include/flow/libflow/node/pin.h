#ifndef FLOW_PIN_H
#define FLOW_PIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
#include <memory>
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class NodeData;

  class LIB_FLOW_API Pin
  {
  public:
    enum class Type;
    using Listener = std::function<void(const NodeData &)>;

  public:
    explicit Pin(std::unique_ptr<NodeData> data, QString caption = {});
    ~Pin();

    [[nodiscard]] const NodeData &getData() const;
    [[nodiscard]] QString getCaption() const;

    void setData(const NodeData &data);
    void setCaption(const QString &caption);

    void addListener(Listener &&listener);
    void clearListeners();

  private:
    void dataChanged(const NodeData &data);

  private:
    std::unique_ptr<NodeData> m_data;
    std::list<Listener> m_listeners;
    QString m_caption;
  };

  enum class Pin::Type
  {
    In,
    Out
  };

}// namespace flow::node

#endif//FLOW_PIN_H
