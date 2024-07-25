#ifndef FLOW_DOCUMENT_OBJECT_H
#define FLOW_DOCUMENT_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
#include <QUuid>
#include <QVariantMap>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/serializable.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Object Qtils ---------------------------- */

#define IMPL_FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS, CLASS_NAME)               \
 public:                                                                      \
  using PARENT_CLASS::isClass;                                                \
  using PARENT_CLASS::isClassOrChild;                                         \
                                                                              \
  static QString sGetClassName() { return CLASS_NAME; }                       \
  [[nodiscard]] QString getClassName() const override { return CLASS_NAME; }  \
                                                                              \
  static QString sGetParentClassName() {                                      \
    return PARENT_CLASS::sGetClassName();                                     \
  }                                                                           \
  [[nodiscard]] QString getParentClassName() const override {                 \
    return PARENT_CLASS::getClassName();                                      \
  }                                                                           \
                                                                              \
  [[nodiscard]] static QStringList sGetInheritedClassNames() {                \
    auto inherited_classes = QStringList{};                                   \
    if (auto parent_class = sGetParentClassName(); !parent_class.isEmpty())   \
      inherited_classes << parent_class;                                      \
    return inherited_classes << PARENT_CLASS::sGetInheritedClassNames();      \
  }                                                                           \
  [[nodiscard]] QStringList getInheritedClassNames() const override {         \
    auto inherited_classes = QStringList{};                                   \
    if (auto parent_class = sGetParentClassName(); !parent_class.isEmpty())   \
      inherited_classes << parent_class;                                      \
    return inherited_classes << PARENT_CLASS::getInheritedClassNames();       \
  }                                                                           \
                                                                              \
  static bool sIsClass(const QString &className) {                            \
    return CLASS::sGetClassName() == className;                               \
  }                                                                           \
                                                                              \
  static bool sIsClassOrChild(const QString &class_name) {                    \
    return sIsClass(class_name) || PARENT_CLASS::sIsClassOrChild(class_name); \
  }                                                                           \
  bool isClassOrChild(const QString &class_name) const override {             \
    return sIsClass(class_name) || PARENT_CLASS::isClassOrChild(class_name);  \
  }                                                                           \
                                                                              \
  template <typename OBJECT>                                                  \
  bool sIsClass() const {                                                     \
    return sIsClass(OBJECT::sGetClassName());                                 \
  }                                                                           \
  template <typename OBJECT>                                                  \
  bool sIsClassOrChild() {                                                    \
    return sIsClassOrChild(OBJECT::sGetClassName());                          \
  }

#define FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS) \
  IMPL_FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS, #CLASS)

namespace flow {

/* ----------------------------------- Object ------------------------------- */

class LIB_FLOW_DOCUMENT_API Object : public qtils::Serializable,
                                     public qtils::Deserializable {
 public:
  explicit Object();
  virtual ~Object();

  [[nodiscard]] QUuid getId() const;

  void setName(const QString &name);
  [[nodiscard]] QString getName() const;

  void setProperty(const QString &name, const QVariant &value);
  [[nodiscard]] QVariant getProperty(const QString &name) const;
  void removeProperty(const QString &name);

  void setProperties(const QVariantMap &properties);
  [[nodiscard]] const QVariantMap &getProperties() const;

  void serialize(qtils::OArchive &archive) const override;
  void deserialize(qtils::IArchive &archive) override;

  [[nodiscard]] static QString sGetClassName();
  [[nodiscard]] virtual QString getClassName() const;

  [[nodiscard]] static QString sGetParentClassName();
  [[nodiscard]] virtual QString getParentClassName() const;

  [[nodiscard]] static QStringList sGetInheritedClassNames();
  [[nodiscard]] virtual QStringList getInheritedClassNames() const;

  [[nodiscard]] static bool sIsClass(const QString &class_name);
  [[nodiscard]] bool isClass(const QString &class_name) const;

  [[nodiscard]] static bool sIsClassOrChild(const QString &class_name);
  [[nodiscard]] virtual bool isClassOrChild(const QString &class_name) const;

  template <typename OBJECT>
  [[nodiscard]] static bool sIsClass();
  template <typename OBJECT>
  [[nodiscard]] bool isClass() const;

  template <typename OBJECT>
  [[nodiscard]] static bool sIsClassOrChild();
  template <typename OBJECT>
  [[nodiscard]] bool isClassOrChild() const;

 protected:
  void init(const Object *object);

 private:
  QUuid m_id;
  QString m_name;
  QVariantMap m_properties;
};

template <typename OBJECT>
bool Object::sIsClass() {
  return sIsClass(OBJECT::sGetClassName());
}

template <typename OBJECT>
bool Object::isClass() const {
  return isClass(OBJECT::sGetClassName());
}

template <typename OBJECT>
bool Object::sIsClassOrChild() {
  return sIsClassOrChild(OBJECT::sGetClassName());
}

template <typename OBJECT>
bool Object::isClassOrChild() const {
  return isClassOrChild(OBJECT::sGetClassName());
}

/* ------------------------------- MoveableObject --------------------------- */

class LIB_FLOW_DOCUMENT_API MoveableObject : public Object {
  FLOW_OBJECT_CLASS(MoveableObject, Object)

 public:
  explicit MoveableObject();
  ~MoveableObject() override;

  void setPosition(const QPointF &position);
  [[nodiscard]] QPointF getPosition() const;

  void serialize(qtils::OArchive &archive) const override;
  void deserialize(qtils::IArchive &archive) override;

 protected:
  void init(const MoveableObject *object);

 private:
  QPointF m_position;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_OBJECT_H