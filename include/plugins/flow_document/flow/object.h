#ifndef FLOW_DOCUMENT_OBJECT_H
#define FLOW_DOCUMENT_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
#include <QUuid>
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Object {
 public:
  explicit Object();
  virtual ~Object();

  [[nodiscard]] QUuid getId() const;

  void setName(const QString &name);
  [[nodiscard]] QString getName() const;

  void setPosition(const QPointF &position);
  [[nodiscard]] QPointF getPosition() const;

  void setProperties(const QVariantMap &properties);
  [[nodiscard]] const QVariantMap &getProperties() const;

  [[nodiscard]] static QString staticClassName() { return "Object"; }
  [[nodiscard]] virtual QString className() const { return "Object"; }

  [[nodiscard]] static QString staticParentClassName() { return ""; }
  [[nodiscard]] virtual QString parentClassName() const { return ""; }

  [[nodiscard]] virtual bool isClass(const QString &className) {
    return Object::className() == className;
  }

 private:
  QUuid m_id;
  QString m_name;
  QPointF m_position;
  QVariantMap m_properties;
};

#define IMPL_FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS, CLASS_NAME)                \
 public:                                                                       \
  static QString staticClassName() { return CLASS_NAME; }                      \
  [[nodiscard]] QString className() const override { return CLASS_NAME; }      \
                                                                               \
  static QString staticParentClassName() {                                     \
    return PARENT_CLASS::staticClassName();                                    \
  }                                                                            \
  [[nodiscard]] QString parentClassName() const override {                     \
    return PARENT_CLASS::className();                                          \
  }                                                                            \
                                                                               \
  bool isClass(const QString &className) override {                            \
    return CLASS::className() == className ? true                              \
                                           : PARENT_CLASS::isClass(className); \
  }

#define FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS) \
  IMPL_FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS, #CLASS)

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_H