/* ----------------------------------- Local -------------------------------- */
#include "logic_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

LogicNodeBoolEmitter::LogicNodeBoolEmitter()
    : m_widget(new QCheckBox(QObject::tr("Bool"))) {
  setName(QObject::tr("BOOL_EMITTER"));

  auto value_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(value_pin),
            PinOut::Result);

  m_widget->connect(m_widget.get(), &QCheckBox::toggled,
                    [this]() { compute(); });
}

LogicNodeBoolEmitter::~LogicNodeBoolEmitter() = default;

QWidget *LogicNodeBoolEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> LogicNodeBoolEmitter::clone() const {
  auto node = std::make_unique<LogicNodeBoolEmitter>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolEmitter::compute() {
  auto &value_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);
  const auto value =
      static_cast<bool>(m_widget->checkState() & Qt::CheckState::Checked);

  value_pin.setData(value);
}

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

LogicNodeBoolReceiver::LogicNodeBoolReceiver()
    : m_widget(new QCheckBox(QObject::tr("Bool"))) {
  setName(QObject::tr("BOOL_RECEIVER"));

  auto result_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(result_pin), PinIn::Value);

  m_widget->setDisabled(true);
}

LogicNodeBoolReceiver::~LogicNodeBoolReceiver() = default;

QWidget *LogicNodeBoolReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> LogicNodeBoolReceiver::clone() const {
  auto node = std::make_unique<LogicNodeBoolReceiver>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolReceiver::compute() {
  auto &result_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  const auto value = result_pin.getData().toBool();

  m_widget->setCheckState(value ? Qt::CheckState::Checked
                                : Qt::CheckState::Unchecked);
}
