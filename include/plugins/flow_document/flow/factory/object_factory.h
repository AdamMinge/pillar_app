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

class Object;

class FLOW_DOCUMENT_API ObjectFactory : public QObject {
  Q_OBJECT

 public:
  enum class Type {
    NodeFactory,
    LayerFactory,
  };

 public:
  explicit ObjectFactory(Type type, QString name, QString section, QIcon icon,
                         QObject* parent = nullptr);
  ~ObjectFactory() override;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
  [[nodiscard]] virtual std::unique_ptr<Object> create() const = 0;

  [[nodiscard]] Type getType() const;
  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getSection() const;
  [[nodiscard]] QIcon getIcon() const;

 private:
  Type m_type;
  QString m_name;
  QString m_section;
  QIcon m_icon;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ObjectFactory, "org.flow.ObjectFactory")

#endif  // FLOW_DOCUMENT_OBJECT_FACTORY_H