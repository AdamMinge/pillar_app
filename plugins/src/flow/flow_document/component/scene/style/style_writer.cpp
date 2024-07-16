/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/style/style_writer.h"

#include "flow_document/component/scene/style/style.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- FlowStyleWriterImpl ------------------------- */

class FlowStyleWriter::FlowStyleWriterImpl {
 public:
  explicit FlowStyleWriterImpl() = default;
  ~FlowStyleWriterImpl() = default;

  void writeStyle(const FlowStyle &style, QIODevice &device);

 private:
  void writeStyle(QJsonDocument &document, const FlowStyle &style);

  [[nodiscard]] QJsonObject writeNodeStyle(const NodeStyle &style);
  [[nodiscard]] QJsonObject writePinStyle(const PinStyle &style);
  [[nodiscard]] QJsonObject writeConnectionStyle(const ConnectionStyle &style);

  [[nodiscard]] static QString convert(const QSizeF &size);
  [[nodiscard]] static QString convert(const QMarginsF &margins);
  [[nodiscard]] static QString convert(const Gradient &colors);
  [[nodiscard]] static QString convert(const GradientScale &scales);
};

void FlowStyleWriter::FlowStyleWriterImpl::writeStyle(const FlowStyle &style,
                                                      QIODevice &device) {
  QJsonDocument document;
  writeStyle(document, style);
  device.write(document.toJson());
}

void FlowStyleWriter::FlowStyleWriterImpl::writeStyle(QJsonDocument &document,
                                                      const FlowStyle &style) {
  auto main = QJsonObject{};
  auto nodes = writeNodeStyle(style.getNodeStyle());
  auto pins = writePinStyle(style.getPinStyle());
  auto connections = writeConnectionStyle(style.getConnectionStyle());

  main[QLatin1String("nodes")] = nodes;
  main[QLatin1String("pins")] = pins;
  main[QLatin1String("connections")] = connections;

  document.setObject(main);
}

QJsonObject FlowStyleWriter::FlowStyleWriterImpl::writeNodeStyle(
    const NodeStyle &style) {
  auto object = QJsonObject{};
  object[QLatin1String("font")] = style.getFont().toString();
  object[QLatin1String("font_color")] = style.getFontColor().name();
  object[QLatin1String("margins")] = convert(style.getMargins());
  object[QLatin1String("gradient")] = convert(style.getGradient());
  object[QLatin1String("gradient_scale")] = convert(style.getGradientScale());
  object[QLatin1String("border_color")] = style.getBorderColor().name();
  object[QLatin1String("border_radius")] = style.getBorderRadius();
  object[QLatin1String("border_size")] = style.getBorderSize();

  return object;
}

QJsonObject FlowStyleWriter::FlowStyleWriterImpl::writePinStyle(
    const PinStyle &style) {
  auto object = QJsonObject{};
  object[QLatin1String("font")] = style.getFont().toString();
  object[QLatin1String("font_color")] = style.getFontColor().name();
  object[QLatin1String("size")] = convert(style.getSize());
  object[QLatin1String("margins")] = convert(style.getMargins());
  object[QLatin1String("color")] = style.getColor().name();
  object[QLatin1String("border_color")] = style.getBorderColor().name();

  return object;
}

QJsonObject FlowStyleWriter::FlowStyleWriterImpl::writeConnectionStyle(
    const ConnectionStyle &style) {
  auto object = QJsonObject{};
  object[QLatin1String("color")] = style.getColor().name();
  object[QLatin1String("thickness")] = style.getThickness();

  return object;
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(const QSizeF &size) {
  return QString("%1;%2").arg(size.width()).arg(size.height());
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(
    const QMarginsF &margins) {
  return QString("%1;%2;%3;%4")
      .arg(margins.left())
      .arg(margins.top())
      .arg(margins.right())
      .arg(margins.bottom());
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(const Gradient &colors) {
  auto str_colors = QStringList{};
  for (const auto &color : colors) str_colors << color.name();
  return QStringList(str_colors).join(';');
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(
    const GradientScale &scales) {
  auto str_colors = QStringList{};
  for (const auto &scale : scales) str_colors << QString::number(scale);
  return QStringList(str_colors).join(';');
}

/* ------------------------------ FlowStyleWriter --------------------------- */

FlowStyleWriter::FlowStyleWriter()
    : m_impl(std::make_unique<FlowStyleWriterImpl>()) {}

FlowStyleWriter::~FlowStyleWriter() = default;

void FlowStyleWriter::write(const FlowStyle &style, QIODevice &device) {
  m_impl->writeStyle(style, device);
}

bool FlowStyleWriter::write(const FlowStyle &style, const QString &file_name,
                            QString *error) {
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return false;
  }

  m_impl->writeStyle(style, file);

  if (file.error() != QFileDevice::NoError) {
    if (error) *error = file.errorString();
    return false;
  }

  file.close();
  return true;
}

}  // namespace flow_document
