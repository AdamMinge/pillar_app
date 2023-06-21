#ifndef FLOW_DOCUMENT_LAYER_FACTORY_H
#define FLOW_DOCUMENT_LAYER_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
#include "flow_document/flow/factory/object_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- LayerFactory ---------------------------- */

class FLOW_DOCUMENT_API LayerFactory : public ObjectFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectFactory)

 public:
  explicit LayerFactory(QString name, QString section,
                        QObject* parent = nullptr);
  explicit LayerFactory(QString name, QString section, QIcon icon,
                        QObject* parent = nullptr);
  ~LayerFactory() override;

  [[nodiscard]] QString getObjectClass() const = 0;
  [[nodiscard]] std::unique_ptr<Object> create() const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::LayerFactory, "org.flow.LayerFactory")

namespace flow_document {

/* ----------------------------- GroupLayerFactory -------------------------- */

class FLOW_DOCUMENT_API GroupLayerFactory : public LayerFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::LayerFactory)

 public:
  explicit GroupLayerFactory(QObject* parent = nullptr);
  ~GroupLayerFactory() override;

  [[nodiscard]] QString getObjectClass() const override;
  [[nodiscard]] std::unique_ptr<Object> create() const override;
};

/* ------------------------------ NodeLayerFactory -------------------------- */

class FLOW_DOCUMENT_API NodeLayerFactory : public LayerFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::LayerFactory)

 public:
  explicit NodeLayerFactory(QObject* parent = nullptr);
  ~NodeLayerFactory() override;

  [[nodiscard]] QString getObjectClass() const override;
  [[nodiscard]] std::unique_ptr<Object> create() const override;
};

/* ----------------------- Helper macro to create factory ------------------- */
// clang-format off
#define DECLARE_LAYER_FACTORY(export_api, layer)                                        \
  class export_api layer##Factory : public flow_document::LayerFactory{                 \
    Q_OBJECT                                                                            \
    Q_INTERFACES(flow_document::LayerFactory)                                           \
    public :                                                                            \
      explicit layer##Factory(QString name, QString section,                            \
                                QObject* parent = nullptr) :                            \
            flow_document::LayerFactory(std::move(name), std::move(section),            \
                                        parent){}                                       \
      explicit layer##Factory(QString name, QString section, QIcon icon,                \
                                QObject* parent = nullptr) :                            \
            flow_document::LayerFactory(std::move(name), std::move(section),            \
                                        std::move(icon), parent){}                      \
                                                                                        \
      [[nodiscard]] QString getObjectClass() const override {                           \
        return layer::getStaticClassName();                                             \
      }                                                                                 \
      [[nodiscard]] std::unique_ptr<flow_document::Object> create() const override {    \
        return std::make_unique<layer>();                                               \
      }                                                                                 \
  };
// clang-format on

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_FACTORY_H