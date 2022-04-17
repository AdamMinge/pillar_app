#ifndef FLOW_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_CONVERTER_FACTORY_CONTAINER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ---------------------------------- Standard ------------------------------ */
#include <memory>
#include <unordered_map>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class ConverterFactory;

  class NODE_API ConverterFactoryContainer : public QObject
  {
    Q_OBJECT

  public:
    explicit ConverterFactoryContainer(QObject *parent = nullptr);
    ~ConverterFactoryContainer() override;

    void addFactory(std::unique_ptr<ConverterFactory> node_factory);
    void removeFactory(const ConverterFactory &node_factory);

    [[nodiscard]] std::list<std::unique_ptr<ConverterFactory>>::const_iterator
    begin() const;
    [[nodiscard]] std::list<std::unique_ptr<ConverterFactory>>::const_iterator
    end() const;

    [[nodiscard]] std::list<std::unique_ptr<ConverterFactory>>::iterator
    begin();
    [[nodiscard]] std::list<std::unique_ptr<ConverterFactory>>::iterator end();

    [[nodiscard]] size_t size() const;

    [[nodiscard]] virtual QString getName() const = 0;
    [[nodiscard]] virtual QIcon getIcon() const = 0;

  private:
    std::list<std::unique_ptr<ConverterFactory>> m_factories;
  };

}// namespace node

Q_DECLARE_INTERFACE(
  node::ConverterFactoryContainer, "org.flow.ConverterFactoryContainer")

#endif//FLOW_CONVERTER_FACTORY_CONTAINER_H
