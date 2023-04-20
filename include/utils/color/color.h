#ifndef UTILS_COLOR_COLOR_H
#define UTILS_COLOR_COLOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "utils/color/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

[[nodiscard]] COLOR_API QString getColorName(const QColor &color);

}  // namespace utils

#endif  // UTILS_COLOR_COLOR_H
