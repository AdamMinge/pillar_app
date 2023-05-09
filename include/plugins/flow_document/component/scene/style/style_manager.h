#ifndef FLOW_DOCUMENT_STYLE_MANAGER_H
#define FLOW_DOCUMENT_STYLE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowStyle;

class FLOW_DOCUMENT_API StyleManager : public QObject {
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
  static QScopedPointer<StyleManager> m_instance;

  std::unique_ptr<FlowStyle> m_style;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_STYLE_MANAGER_H
