#ifndef UTILS_DPI_DPI_H
#define UTILS_DPI_DPI_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPoint>
#include <QRectF>
#include <QSize>
#include <QtGlobal>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/dpi/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

[[nodiscard]] DPI_API int defaultDpi();
[[nodiscard]] DPI_API qreal defaultDpiScale();

[[nodiscard]] DPI_API int dpiScaled(int value);
[[nodiscard]] DPI_API qreal dpiScaled(qreal value);
[[nodiscard]] DPI_API QSize dpiScaled(const QSize &value);
[[nodiscard]] DPI_API QPoint dpiScaled(const QPoint &value);
[[nodiscard]] DPI_API QRectF dpiScaled(const QRectF &value);

}  // namespace utils

#endif  // UTILS_DPI_DPI_H
