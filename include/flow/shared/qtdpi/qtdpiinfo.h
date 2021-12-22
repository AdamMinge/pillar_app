#ifndef FLOW_TOOLS_DPI_INFO_H
#define FLOW_TOOLS_DPI_INFO_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPoint>
#include <QRectF>
#include <QSize>
#include <QtGlobal>
/* -------------------------------------------------------------------------- */

namespace tools
{

  class TOOLS_SHARED_API QtDpiInfo
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

}// namespace tools

#endif//FLOW_TOOLS_DPI_INFO_H
