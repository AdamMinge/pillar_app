#ifndef FLOW_CONVERTER_FACTORY_H
#define FLOW_CONVERTER_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
/* ---------------------------------- Standard ------------------------------ */
#include <functional>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class TypeConverter;

  class NODE_API ConverterFactory
  {
  public:
    using Creator = std::function<std::unique_ptr<TypeConverter>()>;

  public:
    explicit ConverterFactory();
    explicit ConverterFactory(
      QString id, Creator creator, QString name, QIcon icon);
    ~ConverterFactory();

    [[nodiscard]] QString getId() const;
    [[nodiscard]] Creator getCreator() const;
    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

    [[nodiscard]] std::unique_ptr<TypeConverter> operator()() const;

  private:
    QString m_id;
    Creator m_creator;
    QString m_name;
    QIcon m_icon;
  };

}// namespace node

#endif//FLOW_CONVERTER_FACTORY_H
