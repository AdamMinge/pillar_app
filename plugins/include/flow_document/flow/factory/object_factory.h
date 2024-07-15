#ifndef FLOW_DOCUMENT_OBJECT_FACTORY_H
#define FLOW_DOCUMENT_OBJECT_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Object;

/* ------------------------------- ObjectFactory ---------------------------- */

class FLOW_DOCUMENT_API ObjectFactory : public QObject {
  Q_OBJECT

 public:
  using InitMethod = std::function<void(Object*)>;
  static constexpr auto empty_init = [](Object*) {};

 public:
  explicit ObjectFactory(QString type, QString name, QString section,
                         QIcon icon, QObject* parent = nullptr);
  ~ObjectFactory() override;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
  [[nodiscard]] virtual std::unique_ptr<Object> createObject() const = 0;

  [[nodiscard]] virtual bool addObject(FlowDocument* document,
                                       InitMethod init = empty_init) const = 0;
  [[nodiscard]] virtual bool canAddObject(FlowDocument* document) const = 0;

  [[nodiscard]] QString getType() const;
  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getSection() const;
  [[nodiscard]] QIcon getIcon() const;

 private:
  QString m_type;
  QString m_name;
  QString m_section;
  QIcon m_icon;
};

/* ----------------------------------- Qtils -------------------------------- */

[[nodiscard]] ObjectFactory* getObjectFactoryByClassName(
    const QString& class_name);

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ObjectFactory, "org.flow.ObjectFactory")

#endif  // FLOW_DOCUMENT_OBJECT_FACTORY_H