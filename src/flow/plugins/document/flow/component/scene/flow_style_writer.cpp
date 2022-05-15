/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_style_writer.h"
#include "flow/plugins/document/flow/component/scene/flow_style.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
/* -------------------------------------------------------------------------- */

/* ---------------------------- FlowStyleWriterImpl ------------------------- */

class FlowStyleWriter::FlowStyleWriterImpl
{
public:
  explicit FlowStyleWriterImpl() = default;
  ~FlowStyleWriterImpl() = default;

  void writeStyle(const FlowStyle &style, QIODevice &device);

private:
  void writeStyle(QJsonDocument &document, const FlowStyle &style);

  [[nodiscard]] QJsonObject writeNodeStyle(const NodeStyle &style);
  [[nodiscard]] QJsonObject writePinStyle(const PinStyle &style);

  [[nodiscard]] static QString convert(NodeStyle::State state);
  [[nodiscard]] static QString convert(PinStyle::State state);

  [[nodiscard]] static QString convert(const QSizeF &size);
  [[nodiscard]] static QString convert(const QMarginsF &margins);
  [[nodiscard]] static QString convert(const std::array<QColor, 4> &colors);
  [[nodiscard]] static QString convert(const std::array<float, 4> &scales);
};

void FlowStyleWriter::FlowStyleWriterImpl::writeStyle(
  const FlowStyle &style, QIODevice &device)
{
  QJsonDocument document;
  writeStyle(document, style);
  device.write(document.toJson());
}

void FlowStyleWriter::FlowStyleWriterImpl::writeStyle(
  QJsonDocument &document, const FlowStyle &style)
{
  auto main = QJsonObject{};

  auto nodes = QJsonObject{};
  for (auto state :
       {NodeStyle::State::Normal, NodeStyle::State::Selected,
        NodeStyle::State::Hovered})
  {
    nodes[convert(state)] = writeNodeStyle(style.getNodeStyle(state));
  }
  main[QLatin1String("nodes")] = nodes;

  auto pins = QJsonObject{};
  for (auto state :
       {PinStyle::State::Normal, PinStyle::State::Selected,
        PinStyle::State::Hovered})
  {
    pins[convert(state)] = writePinStyle(style.getPinStyle(state));
  }
  main[QLatin1String("pins")] = pins;

  document.setObject(main);
}

QJsonObject
FlowStyleWriter::FlowStyleWriterImpl::writeNodeStyle(const NodeStyle &style)
{
  auto object = QJsonObject{};
  if (style.getFont().has_value())
    object[QLatin1String("font")] = style.findFont().toString();
  if (style.getFontColor().has_value())
    object[QLatin1String("font_color")] = style.findFontColor().name();
  if (style.getMargins().has_value())
    object[QLatin1String("margins")] = convert(style.findMargins());
  if (style.getGradient().has_value())
    object[QLatin1String("gradient")] = convert(style.findGradient());
  if (style.getGradientScale().has_value())
    object[QLatin1String("gradient_scale")] =
      convert(style.findGradientScale());
  if (style.getBorderColor().has_value())
    object[QLatin1String("border_color")] = style.findBorderColor().name();
  if (style.getBorderRadius().has_value())
    object[QLatin1String("border_radius")] = style.findBorderRadius();
  if (style.getBorderSize().has_value())
    object[QLatin1String("border_size")] = style.findBorderSize();

  return object;
}

QJsonObject
FlowStyleWriter::FlowStyleWriterImpl::writePinStyle(const PinStyle &style)
{
  auto object = QJsonObject{};
  if (style.getFont().has_value())
    object[QLatin1String("font")] = style.findFont().toString();
  if (style.getFontColor().has_value())
    object[QLatin1String("font_color")] = style.findFontColor().name();
  if (style.getSize().has_value())
    object[QLatin1String("size")] = convert(style.findSize());
  if (style.getMargins().has_value())
    object[QLatin1String("margins")] = convert(style.findMargins());
  if (style.getColor().has_value())
    object[QLatin1String("color")] = style.findColor().name();
  if (style.getBorderColor().has_value())
    object[QLatin1String("border_color")] = style.findBorderColor().name();

  return object;
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(NodeStyle::State state)
{
  switch (state)
  {
    case NodeStyle::State::Normal:
      return QLatin1String("normal");

    case NodeStyle::State::Selected:
      return QLatin1String("selected");

    case NodeStyle::State::Hovered:
      return QLatin1String("hovered");

    default:
      return {};
  }
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(PinStyle::State state)
{
  switch (state)
  {
    case PinStyle::State::Normal:
      return QLatin1String("normal");

    case PinStyle::State::Selected:
      return QLatin1String("selected");

    case PinStyle::State::Hovered:
      return QLatin1String("hovered");

    default:
      return {};
  }
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(const QSizeF &size)
{
  return QString("%1;%2").arg(size.width()).arg(size.height());
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(const QMarginsF &margins)
{
  return QString("%1;%2;%3;%4")
    .arg(margins.left())
    .arg(margins.top())
    .arg(margins.right())
    .arg(margins.bottom());
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(
  const std::array<QColor, 4> &colors)
{
  auto str_colors = QStringList{};
  for (const auto &color : colors) str_colors << color.name();
  return QStringList(str_colors).join(';');
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(
  const std::array<float, 4> &scales)
{
  auto str_colors = QStringList{};
  for (const auto &scale : scales) str_colors << QString::number(scale);
  return QStringList(str_colors).join(';');
}

/* ------------------------------ FlowStyleWriter --------------------------- */

FlowStyleWriter::FlowStyleWriter()
    : m_impl(std::make_unique<FlowStyleWriterImpl>())
{}

FlowStyleWriter::~FlowStyleWriter() = default;


void FlowStyleWriter::write(const FlowStyle &style, QIODevice &device)
{
  m_impl->writeStyle(style, device);
}

bool FlowStyleWriter::write(
  const FlowStyle &style, const QString &file_name, QString *error)
{
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return false;
  }

  m_impl->writeStyle(style, file);

  if (file.error() != QFileDevice::NoError)
  {
    if (error) *error = file.errorString();
    return false;
  }

  file.close();
  return true;
}
