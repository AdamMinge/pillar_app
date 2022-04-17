#ifndef FLOW_COLOR_H
#define FLOW_COLOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/color/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  [[nodiscard]] COLOR_API QString getColorName(const QColor &color);

}// namespace utils

#endif//FLOW_COLOR_H
