#ifndef FLOW_DOCUMENT_OBJECT_H
#define FLOW_DOCUMENT_OBJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
#include <QUuid>
#include <QVariantMap>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/serializable.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Object ------------------------------- */

class FLOW_DOCUMENT_API Object : public utils::Serializable {
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

  void serialize(utils::OArchive &archive) const override;
  void deserialize(utils::IArchive &archive) override;

  [[nodiscard]] static QString getStaticClassName();
  [[nodiscard]] virtual QString getClassName() const;

  [[nodiscard]] static QString getStaticParentClassName();
  [[nodiscard]] virtual QString getParentClassName() const;

  [[nodiscard]] static QStringList getStaticInheritedClasses();
  [[nodiscard]] virtual QStringList getInheritedClasses() const;

  [[nodiscard]] virtual bool isClass(const QString &class_name) const;
  [[nodiscard]] virtual bool isClassOrChild(const QString &class_name) const;

 protected:
  void init(const Object *object);

 private:
  QUuid m_id;
  QString m_name;
  QVariantMap m_properties;
};

/* -------------------------------- Object Utils ---------------------------- */

#define IMPL_FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS, CLASS_NAME)              \
 public:                                                                     \
  static QString getStaticClassName() { return CLASS_NAME; }                 \
  [[nodiscard]] QString getClassName() const override { return CLASS_NAME; } \
                                                                             \
  static QString getStaticParentClassName() {                                \
    return PARENT_CLASS::getStaticClassName();                               \
  }                                                                          \
  [[nodiscard]] QString getParentClassName() const override {                \
    return PARENT_CLASS::getClassName();                                     \
  }                                                                          \
                                                                             \
  [[nodiscard]] static QStringList getStaticInheritedClasses() {             \
    auto inherited_classes = QStringList{};                                  \
    if (auto parent_class = getStaticParentClassName();                      \
        !parent_class.isEmpty())                                             \
      inherited_classes << parent_class;                                     \
    return inherited_classes << PARENT_CLASS::getStaticInheritedClasses();   \
  }                                                                          \
  [[nodiscard]] QStringList getInheritedClasses() const override {           \
    auto inherited_classes = QStringList{};                                  \
    if (auto parent_class = getStaticParentClassName();                      \
        !parent_class.isEmpty())                                             \
      inherited_classes << parent_class;                                     \
    return inherited_classes << PARENT_CLASS::getInheritedClasses();         \
  }                                                                          \
                                                                             \
  bool isClass(const QString &className) const override {                    \
    return CLASS::getClassName() == className                                \
               ? true                                                        \
               : PARENT_CLASS::isClass(className);                           \
  }                                                                          \
                                                                             \
  bool isClassOrChild(const QString &class_name) const override {            \
    return isClass(class_name) || PARENT_CLASS::isClassOrChild(class_name);  \
  }

#define FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS) \
  IMPL_FLOW_OBJECT_CLASS(CLASS, PARENT_CLASS, #CLASS)

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_H