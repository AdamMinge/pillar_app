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

  [[nodiscard]] QJsonObject writeNodeStyle(const NodeStyle &style,
                                           ObjectStyle::State state);
  [[nodiscard]] QJsonObject writePinStyle(const PinStyle &style,
                                          ObjectStyle::State state);

  [[nodiscard]] static QString convert(ObjectStyle::State state);
  [[nodiscard]] static QString convert(const QSizeF &size);
  [[nodiscard]] static QString convert(const QMarginsF &margins);
  [[nodiscard]] static QString convert(const Gradient &colors);
  [[nodiscard]] static QString convert(const GradientScale &scales);

  template <typename STYLE, typename PROPERTY>
  [[nodiscard]] bool stylePropIsOverridden(
      const STYLE &style, PROPERTY (STYLE::*getter)(ObjectStyle::States) const,
      ObjectStyle::State state) {
    return state == ObjectStyle::State::Normal ||
           (style.*getter)(ObjectStyle::State::Normal) !=
               (style.*getter)(state);
  }
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

  auto nodes = QJsonObject{};
  for (auto state : {ObjectStyle::State::Normal, ObjectStyle::State::Selected,
                     ObjectStyle::State::Hovered}) {
    nodes[convert(state)] = writeNodeStyle(style.getNodeStyle(), state);
  }
  main[QLatin1String("nodes")] = nodes;

  auto pins = QJsonObject{};
  for (auto state : {ObjectStyle::State::Normal, ObjectStyle::State::Selected,
                     ObjectStyle::State::Hovered}) {
    pins[convert(state)] = writePinStyle(style.getPinStyle(), state);
  }
  main[QLatin1String("pins")] = pins;

  document.setObject(main);
}

QJsonObject FlowStyleWriter::FlowStyleWriterImpl::writeNodeStyle(
    const NodeStyle &style, ObjectStyle::State state) {
  auto propIsOverridden = [&](auto prop_getter) {
    return stylePropIsOverridden(style, prop_getter, state);
  };

  auto object = QJsonObject{};

  if (propIsOverridden(&NodeStyle::getFont))
    object[QLatin1String("font")] = style.getFont(state).toString();
  if (propIsOverridden(&NodeStyle::getFontColor))
    object[QLatin1String("font_color")] = style.getFontColor(state).name();
  if (propIsOverridden(&NodeStyle::getMargins))
    object[QLatin1String("margins")] = convert(style.getMargins(state));
  if (propIsOverridden(&NodeStyle::getGradient))
    object[QLatin1String("gradient")] = convert(style.getGradient(state));
  if (propIsOverridden(&NodeStyle::getGradientScale))
    object[QLatin1String("gradient_scale")] =
        convert(style.getGradientScale(state));
  if (propIsOverridden(&NodeStyle::getBorderColor))
    object[QLatin1String("border_color")] = style.getBorderColor(state).name();
  if (propIsOverridden(&NodeStyle::getBorderRadius))
    object[QLatin1String("border_radius")] = style.getBorderRadius(state);
  if (propIsOverridden(&NodeStyle::getBorderSize))
    object[QLatin1String("border_size")] = style.getBorderSize(state);

  return object;
}

QJsonObject FlowStyleWriter::FlowStyleWriterImpl::writePinStyle(
    const PinStyle &style, ObjectStyle::State state) {
  auto propIsOverridden = [&](auto prop_getter) {
    return stylePropIsOverridden(style, prop_getter, state);
  };

  auto object = QJsonObject{};

  if (propIsOverridden(&PinStyle::getFont))
    object[QLatin1String("font")] = style.getFont(state).toString();
  if (propIsOverridden(&PinStyle::getFontColor))
    object[QLatin1String("font_color")] = style.getFontColor(state).name();
  if (propIsOverridden(&PinStyle::getSize))
    object[QLatin1String("size")] = convert(style.getSize(state));
  if (propIsOverridden(&PinStyle::getMargins))
    object[QLatin1String("margins")] = convert(style.getMargins(state));
  if (propIsOverridden(&PinStyle::getColor))
    object[QLatin1String("color")] = style.getColor(state).name();
  if (propIsOverridden(&PinStyle::getBorderColor))
    object[QLatin1String("border_color")] = style.getBorderColor(state).name();

  return object;
}

QString FlowStyleWriter::FlowStyleWriterImpl::convert(
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
