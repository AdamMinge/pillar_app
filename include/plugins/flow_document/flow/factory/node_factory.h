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
  static constexpr QLatin1String type = QLatin1String("Nodes");

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

#define DECLARE_NODE_FACTORY(EXPORT_API, NODE)                            \
  class EXPORT_API NODE##Factory : public flow_document::NodeFactory {    \
    Q_OBJECT                                                              \
    Q_INTERFACES(flow_document::NodeFactory)                              \
   public:                                                                \
    explicit NODE##Factory(QString name, QString section,                 \
                           QObject* parent = nullptr)                     \
        : flow_document::NodeFactory(std::move(name), std::move(section), \
                                     parent) {}                           \
    explicit NODE##Factory(QString name, QString section, QIcon icon,     \
                           QObject* parent = nullptr)                     \
        : flow_document::NodeFactory(std::move(name), std::move(section), \
                                     std::move(icon), parent) {}          \
                                                                          \
    [[nodiscard]] QString getObjectClassName() const override {           \
      return NODE::sGetClassName();                                       \
    }                                                                     \
    [[nodiscard]] std::unique_ptr<flow_document::Object> create()         \
        const override {                                                  \
      return std::make_unique<NODE>();                                    \
    }                                                                     \
  };

#endif  // FLOW_DOCUMENT_NODE_FACTORY_H