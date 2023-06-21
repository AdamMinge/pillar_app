#ifndef FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H
#define FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ObjectProperties;
class LayerProperties;
class NodeProperties;

/* -------------------------- ObjectPropertiesFactory ----------------------- */

class FLOW_DOCUMENT_API ObjectPropertiesFactory : public QObject {
  Q_OBJECT

 public:
  explicit ObjectPropertiesFactory(QObject* parent = nullptr);
  ~ObjectPropertiesFactory() override;

  [[nodiscard]] virtual ObjectProperties* create(
      QObject* parent = nullptr) const = 0;

  [[nodiscard]] virtual QString getObjectClass() const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ObjectPropertiesFactory,
                    "org.flow.ObjectPropertiesFactory")

namespace flow_document {

/* --------------------------- LayerPropertiesFactory ----------------------- */

class LayerPropertiesFactory : public ObjectPropertiesFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectPropertiesFactory)

 public:
  explicit LayerPropertiesFactory(QObject* parent = nullptr);

  [[nodiscard]] ObjectProperties* create(
      QObject* parent = nullptr) const override;

  [[nodiscard]] QString getObjectClass() const override;
};

/* --------------------------- NodePropertiesFactory ------------------------ */

class NodePropertiesFactory : public ObjectPropertiesFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectPropertiesFactory)

 public:
  explicit NodePropertiesFactory(QObject* parent = nullptr);

  [[nodiscard]] ObjectProperties* create(
      QObject* parent = nullptr) const override;

  [[nodiscard]] QString getObjectClass() const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H