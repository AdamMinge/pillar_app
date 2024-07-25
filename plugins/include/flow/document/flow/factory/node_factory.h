#ifndef FLOW_DOCUMENT_NODE_FACTORY_H
#define FLOW_DOCUMENT_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/concept.h"
#include "flow/document/export.h"
#include "flow/document/flow/factory/object_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------------- NodeFactory ----------------------------- */

class LIB_FLOW_DOCUMENT_API NodeFactory : public ObjectFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ObjectFactory)

 public:
  static constexpr QLatin1String type = QLatin1String("Nodes");

 public:
  explicit NodeFactory(QString name, QString section,
                       QObject* parent = nullptr);
  explicit NodeFactory(QString name, QString section, QIcon icon,
                       QObject* parent = nullptr);
  ~NodeFactory() override;

  [[nodiscard]] QString getObjectClassName() const = 0;
  [[nodiscard]] std::unique_ptr<Object> createObject() const = 0;

  [[nodiscard]] bool addObject(FlowDocument* document,
                               InitMethod init = empty_init) const override;
  [[nodiscard]] bool canAddObject(FlowDocument* document) const override;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::NodeFactory, "org.flow.NodeFactory")

#define DECLARE_NODE_FACTORY(EXPORT_API, NODE)                              \
  class EXPORT_API NODE##Factory : public flow::NodeFactory {               \
    Q_OBJECT                                                                \
    Q_INTERFACES(flow::NodeFactory)                                         \
   public:                                                                  \
    explicit NODE##Factory(QString name, QString section,                   \
                           QObject* parent = nullptr)                       \
        : flow::NodeFactory(std::move(name), std::move(section), parent) {} \
    explicit NODE##Factory(QString name, QString section, QIcon icon,       \
                           QObject* parent = nullptr)                       \
        : flow::NodeFactory(std::move(name), std::move(section),            \
                            std::move(icon), parent) {}                     \
                                                                            \
    [[nodiscard]] QString getObjectClassName() const override {             \
      return NODE::sGetClassName();                                         \
    }                                                                       \
    [[nodiscard]] std::unique_ptr<flow::Object> createObject()              \
        const override {                                                    \
      return std::make_unique<NODE>();                                      \
    }                                                                       \
  };

#endif  // FLOW_DOCUMENT_NODE_FACTORY_H