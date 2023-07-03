#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/object_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class Shape;

class SHAPE_API ShapeFactory : public flow_document::ObjectFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectFactory)

 public:
  static constexpr QLatin1String type = QLatin1String("ShapeFactory");

 public:
  explicit ShapeFactory(QString name, QString section,
                        QObject* parent = nullptr);
  explicit ShapeFactory(QString name, QString section, QIcon icon,
                        QObject* parent = nullptr);
  ~ShapeFactory() override;

  [[nodiscard]] QString getObjectClassName() const = 0;
  [[nodiscard]] std::unique_ptr<flow_document::Object> createObject() const = 0;
};

#endif  // SHAPE_FACTORY_H
