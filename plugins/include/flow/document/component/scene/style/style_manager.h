#ifndef FLOW_DOCUMENT_STYLE_MANAGER_H
#define FLOW_DOCUMENT_STYLE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowStyle;

class LIB_FLOW_DOCUMENT_API StyleManager : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static StyleManager &getInstance();
  static void deleteInstance();

 public:
  ~StyleManager() override;

  void setStyle(const FlowStyle &style);
  void resetStyle();

  bool loadStyle(const QString &file_name);
  bool saveStyle(const QString &file_name);

  [[nodiscard]] const FlowStyle &getStyle() const;

 private:
  explicit StyleManager();

 private:
  static std::unique_ptr<StyleManager> m_instance;

  std::unique_ptr<FlowStyle> m_style;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_STYLE_MANAGER_H
