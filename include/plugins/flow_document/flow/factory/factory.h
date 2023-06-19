#ifndef FLOW_DOCUMENT_FACTORY_H
#define FLOW_DOCUMENT_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Factory : public QObject {
  Q_OBJECT

 public:
  enum class Type {
    NodeFactory,
    LayerFactory,
  };

 public:
  explicit Factory(Type type, QString name, QString section, QIcon icon,
                   QObject* parent = nullptr);
  ~Factory() override;

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

Q_DECLARE_INTERFACE(flow_document::Factory, "org.flow.Factory")

#endif  // FLOW_DOCUMENT_FACTORY_H