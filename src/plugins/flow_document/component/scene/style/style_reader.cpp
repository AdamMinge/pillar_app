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

  void readNodeStyle(NodeStyle &styles, ObjectStyle::State state,
                     const QJsonObject &object);
  void readPinStyle(PinStyle &styles, ObjectStyle::State state,
                    const QJsonObject &object);

  [[nodiscard]] static QString toString(ObjectStyle::State state);
  [[nodiscard]] static std::optional<QFont> toFont(const QJsonValue &value);
  [[nodiscard]] static std::optional<QColor> toColor(const QJsonValue &value);
  [[nodiscard]] static std::optional<QSizeF> toSize(const QJsonValue &value);
  [[nodiscard]] static std::optional<QMarginsF> toMargins(
      const QJsonValue &value);
  [[nodiscard]] static std::optional<std::array<QColor, 4>> toColors(
      const QJsonValue &value);
  [[nodiscard]] static std::optional<std::array<float, 4>> toScales(
      const QJsonValue &value);
  [[nodiscard]] static std::optional<float> toFloat(const QJsonValue &value);
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

  auto node_style = NodeStyle{};
  for (auto state : {ObjectStyle::State::Normal, ObjectStyle::State::Selected,
                     ObjectStyle::State::Hovered}) {
    const auto state_name = toString(state);
    if (!nodes.contains(state_name)) return nullptr;
    readNodeStyle(node_style, state, nodes[state_name].toObject());
  }
  flow_style->setNodeStyle(node_style);

  auto pin_style = PinStyle{};
  for (auto state : {ObjectStyle::State::Normal, ObjectStyle::State::Selected,
                     ObjectStyle::State::Hovered}) {
    const auto state_name = toString(state);
    if (!pins.contains(state_name)) return nullptr;
    readPinStyle(pin_style, state, pins[state_name].toObject());
  }
  flow_style->setPinStyle(pin_style);

  return flow_style;
}

void FlowStyleReader::FlowStyleReaderImpl::readNodeStyle(
    NodeStyle &styles, ObjectStyle::State state, const QJsonObject &object) {
  styles.setFont(toFont(object[QLatin1String("font")]), state);
  styles.setFontColor(toColor(object[QLatin1String("font_color")]), state);
  styles.setMargins(toMargins(object[QLatin1String("margins")]), state);
  styles.setGradient(toColors(object[QLatin1String("gradient")]), state);
  styles.setGradientScale(toScales(object[QLatin1String("gradient_scale")]),
                          state);
  styles.setBorderColor(toColor(object[QLatin1String("border_color")]), state);
  styles.setBorderRadius(toFloat(object[QLatin1String("border_radius")]),
                         state);
  styles.setBorderSize(toFloat(object[QLatin1String("border_size")]), state);
}

void FlowStyleReader::FlowStyleReaderImpl::readPinStyle(
    PinStyle &styles, ObjectStyle::State state, const QJsonObject &object) {
  styles.setFont(toFont(object[QLatin1String("font")]), state);
  styles.setFontColor(toColor(object[QLatin1String("font_color")]), state);
  styles.setSize(toSize(object[QLatin1String("size")]), state);
  styles.setMargins(toMargins(object[QLatin1String("margins")]), state);
  styles.setColor(toColor(object[QLatin1String("color")]), state);
  styles.setBorderColor(toColor(object[QLatin1String("border_color")]), state);
}

QString FlowStyleReader::FlowStyleReaderImpl::toString(
    ObjectStyle::State state) {
  switch (state) {
    case ObjectStyle::State::Normal:
      return QLatin1String("normal");

    case ObjectStyle::State::Selected:
      return QLatin1String("selected");

    case ObjectStyle::State::Hovered:
      return QLatin1String("hovered");

    default:
      return {};
  }
}

std::optional<QFont> FlowStyleReader::FlowStyleReaderImpl::toFont(
    const QJsonValue &value) {
  auto font = QFont();
  const auto str = value.toString();
  if (!str.isEmpty() && font.fromString(str)) return font;

  return {};
}

std::optional<QColor> FlowStyleReader::FlowStyleReaderImpl::toColor(
    const QJsonValue &value) {
  if (auto color = QColor(value.toString()); color.isValid()) return color;
  return {};
}

std::optional<QSizeF> FlowStyleReader::FlowStyleReaderImpl::toSize(
    const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 2) {
    auto width = toFloat(split[0]);
    auto height = toFloat(split[1]);
    if (width && height) return QSizeF(*width, *height);
  }

  return {};
}

std::optional<QMarginsF> FlowStyleReader::FlowStyleReaderImpl::toMargins(
    const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 4) {
    auto left = toFloat(split[0]);
    auto top = toFloat(split[1]);
    auto right = toFloat(split[2]);
    auto bottom = toFloat(split[3]);

    if (left && top && right && bottom)
      return QMarginsF(*left, *top, *right, *bottom);
  }

  return {};
}

std::optional<std::array<QColor, 4>>
FlowStyleReader::FlowStyleReaderImpl::toColors(const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 4) {
    auto c1 = toColor(split[0]);
    auto c2 = toColor(split[1]);
    auto c3 = toColor(split[2]);
    auto c4 = toColor(split[3]);

    if (c1 && c2 && c3 && c4) {
      return std::array<QColor, 4>{c1.value(), c2.value(), c3.value(),
                                   c4.value()};
    }
  }

  return {};
}

std::optional<std::array<float, 4>>
FlowStyleReader::FlowStyleReaderImpl::toScales(const QJsonValue &value) {
  auto split = value.toString().split(';');
  if (split.size() == 4) {
    auto s1 = toFloat(split[0]);
    auto s2 = toFloat(split[1]);
    auto s3 = toFloat(split[2]);
    auto s4 = toFloat(split[3]);

    if (s1 && s2 && s3 && s4) {
      return std::array<float, 4>{s1.value(), s2.value(), s3.value(),
                                  s4.value()};
    }
  }

  return {};
}

std::optional<float> FlowStyleReader::FlowStyleReaderImpl::toFloat(
    const QJsonValue &value) {
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