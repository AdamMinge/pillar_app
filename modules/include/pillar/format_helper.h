#ifndef PILLAR_FORMAT_HELPER_H
#define PILLAR_FORMAT_HELPER_H

/* ----------------------------------- Local -------------------------------- */
#include "pillar/concept.h"
#include "pillar/export.h"
#include "pillar/file_format.h"
#include "pillar/plugin_manager.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

template <IsFileFormat FORMAT>
class LIB_PILLAR_API FormatHelper {
 public:
  explicit FormatHelper(FileFormat::Capabilities capabilities);

  [[nodiscard]] const QString &getFilter() const;
  [[nodiscard]] const QList<FORMAT *> &getFormats() const;

  [[nodiscard]] FORMAT *findFormatByFileName(const QString &file_name) const;
  [[nodiscard]] FORMAT *findFormatByShortName(const QString &short_name) const;
  [[nodiscard]] FORMAT *findFormatByNameFilter(
      const QString &name_filter) const;

 private:
  QList<FORMAT *> m_formats;
  QString m_filter;
};

template <IsFileFormat FORMAT>
FormatHelper<FORMAT>::FormatHelper(FileFormat::Capabilities capabilities) {
  PluginManager::getInstance().forEach<FORMAT>(
      [this, capabilities](auto format) {
        if (format->hasCapabilities(capabilities)) {
          if (!m_filter.isEmpty()) m_filter += QStringLiteral(";;");
          m_filter += format->getNameFilter();

          m_formats.append(format);
        }
      });
}

template <IsFileFormat FORMAT>
const QString &FormatHelper<FORMAT>::getFilter() const {
  return m_filter;
}

template <IsFileFormat FORMAT>
const QList<FORMAT *> &FormatHelper<FORMAT>::getFormats() const {
  return m_formats;
}

template <IsFileFormat FORMAT>
FORMAT *FormatHelper<FORMAT>::findFormatByFileName(
    const QString &file_name) const {
  auto found_format = std::find_if(
      m_formats.begin(), m_formats.end(),
      [&file_name](auto format) { return format->supportsFile(file_name); });

  return found_format != m_formats.end() ? *found_format : nullptr;
}

template <IsFileFormat FORMAT>
FORMAT *FormatHelper<FORMAT>::findFormatByShortName(
    const QString &short_name) const {
  auto found_format = std::find_if(
      m_formats.begin(), m_formats.end(), [&short_name](auto format) {
        return format->getShortName() == short_name;
      });

  return found_format != m_formats.end() ? *found_format : nullptr;
}

template <IsFileFormat FORMAT>
FORMAT *FormatHelper<FORMAT>::findFormatByNameFilter(
    const QString &name_filter) const {
  auto found_format = std::find_if(
      m_formats.begin(), m_formats.end(), [&name_filter](auto format) {
        return format->getNameFilter() == name_filter;
      });

  return found_format != m_formats.end() ? *found_format : nullptr;
}

}  // namespace pillar

#endif  // PILLAR_FORMAT_HELPER_H
