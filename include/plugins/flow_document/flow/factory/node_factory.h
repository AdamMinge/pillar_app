#ifndef FLOW_DOCUMENT_NODE_FACTORY_H
#define FLOW_DOCUMENT_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
#include "flow_document/flow/factory/object_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- NodeFactory ----------------------------- */

class FLOW_DOCUMENT_API NodeFactory : public ObjectFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectFactory)

 public:
  explicit NodeFactory(QString name, QString section,
                       QObject* parent = nullptr);
  explicit NodeFactory(QString name, QString section, QIcon icon,
                       QObject* parent = nullptr);
  ~NodeFactory() override;

  [[nodiscard]] QString getObjectClassName() const = 0;
  [[nodiscard]] std::unique_ptr<Object> create() const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::NodeFactory, "org.flow.NodeFactory")

namespace flow_document {

/* ----------------------- Helper macro to create factory ------------------- */

// clang-format off
#define DECLARE_NODE_FACTORY(export_api, node)                                          \
  class export_api node##Factory : public flow_document::NodeFactory{                   \
    Q_OBJECT                                                                            \
    Q_INTERFACES(flow_document::NodeFactory)                                            \
    public :                                                                            \
      explicit node##Factory(QString name, QString section,                             \
                                QObject* parent = nullptr) :                            \
            flow_document::NodeFactory(std::move(name), std::move(section),             \
                                        parent){}                                       \
      explicit node##Factory(QString name, QString section, QIcon icon,                 \
                                QObject* parent = nullptr) :                            \
            flow_document::NodeFactory(std::move(name), std::move(section),             \
                                        std::move(icon), parent){}                      \
                                                                                        \
      [[nodiscard]] QString getObjectClassName() const override {                           \
        return node::getStaticClassName();                                              \
      }                                                                                 \
      [[nodiscard]] std::unique_ptr<flow_document::Object> create() const override {    \
        return std::make_unique<node>();                                                \
      }                                                                                 \
  };
// clang-format on

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_FACTORY_H