#ifndef FLOW_DOCUMENT_LAYER_FACTORY_H
#define FLOW_DOCUMENT_LAYER_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/concept.h"
#include "flow/document/export.h"
#include "flow/document/flow/factory/object_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------------- LayerFactory ---------------------------- */

class LIB_FLOW_DOCUMENT_API LayerFactory : public ObjectFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ObjectFactory)

 public:
  static constexpr QLatin1String type = QLatin1String("Layers");

 public:
  explicit LayerFactory(QString name, QString section,
                        QObject* parent = nullptr);
  explicit LayerFactory(QString name, QString section, QIcon icon,
                        QObject* parent = nullptr);
  ~LayerFactory() override;

  [[nodiscard]] QString getObjectClassName() const = 0;
  [[nodiscard]] std::unique_ptr<Object> createObject() const = 0;

  [[nodiscard]] bool addObject(FlowDocument* document,
                               InitMethod init = empty_init) const override;
  [[nodiscard]] bool canAddObject(FlowDocument* document) const override;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::LayerFactory, "org.flow.LayerFactory")

namespace flow {

/* ----------------------------- GroupLayerFactory -------------------------- */

class LIB_FLOW_DOCUMENT_API GroupLayerFactory : public LayerFactory {
  Q_OBJECT
  Q_INTERFACES(flow::LayerFactory)

 public:
  explicit GroupLayerFactory(QObject* parent = nullptr);
  ~GroupLayerFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] std::unique_ptr<Object> createObject() const override;
};

/* ------------------------------ NodeLayerFactory -------------------------- */

class LIB_FLOW_DOCUMENT_API NodeLayerFactory : public LayerFactory {
  Q_OBJECT
  Q_INTERFACES(flow::LayerFactory)

 public:
  explicit NodeLayerFactory(QObject* parent = nullptr);
  ~NodeLayerFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;
  [[nodiscard]] std::unique_ptr<Object> createObject() const override;
};

}  // namespace flow

/* ----------------------- Helper macro to create factory ------------------- */

#define DECLARE_LAYER_FACTORY(EXPORT_API, LAYER)                             \
  class EXPORT_API LAYER##Factory : public flow::LayerFactory {              \
    Q_OBJECT                                                                 \
    Q_INTERFACES(flow::LayerFactory)                                         \
   public:                                                                   \
    explicit LAYER##Factory(QString name, QString section,                   \
                            QObject* parent = nullptr)                       \
        : flow::LayerFactory(std::move(name), std::move(section), parent) {} \
    explicit LAYER##Factory(QString name, QString section, QIcon icon,       \
                            QObject* parent = nullptr)                       \
        : flow::LayerFactory(std::move(name), std::move(section),            \
                             std::move(icon), parent) {}                     \
                                                                             \
    [[nodiscard]] QString getObjectClassName() const override {              \
      return LAYER::sGetClassName();                                         \
    }                                                                        \
    [[nodiscard]] std::unique_ptr<flow::Object> createObject()               \
        const override {                                                     \
      return std::make_unique<LAYER>();                                      \
    }                                                                        \
  };

#endif  // FLOW_DOCUMENT_LAYER_FACTORY_H