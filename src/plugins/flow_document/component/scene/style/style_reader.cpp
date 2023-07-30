/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/style/style_reader.h"

#include "flow_document/component/scene/style/style.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- FlowDocumentReaderImpl ----------------------- */

class FlowStyleReader::FlowStyleReaderImpl {
 public:
  explicit FlowStyleReaderImpl() = default;
  ~FlowStyleReaderImpl() = default;

  std::unique_ptr<FlowStyle> readStyle(QIODevice &device);

 private:
  std::unique_ptr<FlowStyle> readStyle(const QJsonDocument &document);

  [[nodiscard]] NodeStyle readNodeStyle(const QJsonObject &object);
  [[nodiscard]] PinStyle readPinStyle(const QJsonObject &object);
  [[nodiscard]] ConnectionStyle readConnectionStyle(const QJsonObject &object);

  [[nodiscard]] static QFont toFont(const QJsonValue &value);
  [[nodiscard]] static QColor toColor(const QJsonValue &value);
  [[nodiscard]] static QSizeF toSize(const QJsonValue &value);
  [[nodiscard]] static QMarginsF toMargins(const QJsonValue &value);
  [[nodiscard]] static std::array<QColor, 4> toColors(const QJsonValue &value);
  [[nodiscard]] static std::array<float, 4> toScales(const QJsonValue &value);
  [[nodiscard]] static float toFloat(const QJsonValue &value);
};

std::unique_ptr<FlowStyle> FlowStyleReader::FlowStyleReaderImpl::readStyle(
    QIODevice &device) {
  auto document = QJsonDocument::fromJson(device.readAll());
  return readStyle(document);
}

std::unique_ptr<FlowStyle> FlowStyleReader::FlowStyleReaderImpl::readStyle(
    const QJsonDocument &document) {
  const auto main = document.object();
  if (!main.contains(QLatin1String("nodes"))) return nullptr;
  if (!main.contains(QLatin1String("pins"))) return nullptr;

  auto flow_style = std::make_unique<FlowStyle>();
  const auto nodes = main[QLatin1String("nodes")].toObject();
  const auto pins = main[QLatin1String("pins")].toObject();
  const auto connections = main[QLatin1String("connections")].toObject();

  auto node_style = readNodeStyle(nodes);
  auto pin_style = readPinStyle(pins);
  auto connection_style = readConnectionStyle(connections);

  flow_style->setNodeStyle(node_style);
  flow_style->setPinStyle(pin_style);
  flow_style->setConnectionStyle(connection_style);

  return flow_style;
}

NodeStyle FlowStyleReader::FlowStyleReaderImpl::readNodeStyle(
    const QJsonObject &object) {
  auto style = NodeStyle{};
  style.setFont(toFont(object[QLatin1String("font")]));
  style.setFontColor(toColor(object[QLatin1String("font_color")]));
  style.setMargins(toMargins(object[QLatin1String("margins")]));
  style.setGradient(toColors(object[QLatin1String("gradient")]));
  style.setGradientScale(toScales(object[QLatin1String("gradient_scale")]));
  style.setBorderColor(toColor(object[QLatin1String("border_color")]));
  style.setBorderRadius(toFloat(object[QLatin1String("border_radius")]));
  style.setBorderSize(toFloat(object[QLatin1String("border_size")]));

  return style;
}

PinStyle FlowStyleReader::FlowStyleReaderImpl::readPinStyle(
    const QJsonObject &object) {
  auto style = PinStyle{};
  style.setFont(toFont(object[QLatin1String("font")]));
  style.setFontColor(toColor(object[QLatin1String("font_color")]));
  style.setSize(toSize(object[QLatin1String("size")]));
  style.setMargins(toMargins(object[QLatin1String("margins")]));
  style.setColor(toColor(object[QLatin1String("color")]));
  style.setBorderColor(toColor(object[QLatin1String("border_color")]));

  return style;
}

ConnectionStyle FlowStyleReader::FlowStyleReaderImpl::readConnectionStyle(
    const QJsonObject &object) {
  auto style = ConnectionStyle{};
  style.setColor(toColor(object[QLatin1String("color")]));
  style.setThickness(toFloat(object[QLatin1String("thickness")]));

  return style;
}

QFont FlowStyleReader::FlowStyleReaderImpl::toFont(const QJsonValue &value) {
  auto font = QFont();
  const auto str = value.toString();
  if (!str.isEmpty() && font.fromString(str)) return font;

  return {};
}

QColor FlowStyleReader::FlowStyleReaderImpl::toColor(const QJsonValue &value) {
  if (auto color = QColor(value.toString()); color.isValid()) return color;
  return {};
}

QSizeF FlowStyleReader::FlowStyleReaderImpl::toSize(const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 2) {
    auto width = toFloat(split[0]);
    auto height = toFloat(split[1]);
    if (width && height) return QSizeF(width, height);
  }

  return {};
}

QMarginsF FlowStyleReader::FlowStyleReaderImpl::toMargins(
    const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 4) {
    auto left = toFloat(split[0]);
    auto top = toFloat(split[1]);
    auto right = toFloat(split[2]);
    auto bottom = toFloat(split[3]);

    if (left && top && right && bottom)
      return QMarginsF(left, top, right, bottom);
  }

  return {};
}

std::array<QColor, 4> FlowStyleReader::FlowStyleReaderImpl::toColors(
    const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 4) {
    return std::array<QColor, 4>{toColor(split[0]), toColor(split[1]),
                                 toColor(split[2]), toColor(split[3])};
  }

  return {};
}

std::array<float, 4> FlowStyleReader::FlowStyleReaderImpl::toScales(
    const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 4) {
    return std::array<float, 4>{toFloat(split[0]), toFloat(split[1]),
                                toFloat(split[2]), toFloat(split[3])};
  }

  return {};
}

float FlowStyleReader::FlowStyleReaderImpl::toFloat(const QJsonValue &value) {
  if (value.isString()) {
    bool ok;
    auto width = value.toString().toDouble(&ok);
    if (ok) return width;
  } else if (value.isDouble()) {
    return value.toDouble();
  }

  return {};
}

/* ------------------------------ FlowStyleReader --------------------------- */

FlowStyleReader::FlowStyleReader()
    : m_impl(std::make_unique<FlowStyleReaderImpl>()) {}

FlowStyleReader::~FlowStyleReader() = default;

std::unique_ptr<FlowStyle> FlowStyleReader::read(QIODevice &device,
                                                 QString *error) {
  auto style = m_impl->readStyle(device);
  if (!style && error) *error = QObject::tr("Failed to load flow style");
  return style;
}

std::unique_ptr<FlowStyle> FlowStyleReader::read(const QString &file_name,
                                                 QString *error) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return nullptr;
  }

  auto style = m_impl->readStyle(file);
  if (!style && error) *error = QObject::tr("Failed to load flow style");

  return style;
}

}  // namespace flow_document