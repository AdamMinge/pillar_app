#ifndef FLOW_DPI_INFO_H
#define FLOW_DPI_INFO_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPoint>
#include <QRectF>
#include <QSize>
#include <QtGlobal>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/dpi/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class DPI_API QtDpiInfo
  {
  public:
    [[nodiscard]] static int defaultDpi();
    [[nodiscard]] static qreal defaultDpiScale();

    [[nodiscard]] static int dpiScaled(int value);
    [[nodiscard]] static qreal dpiScaled(qreal value);
    [[nodiscard]] static QSize dpiScaled(const QSize &value);
    [[nodiscard]] static QPoint dpiScaled(const QPoint &value);
    [[nodiscard]] static QRectF dpiScaled(const QRectF &value);

  private:
    QtDpiInfo() = default;
  };

}// namespace utils

#endif//FLOW_DPI_INFO_H
