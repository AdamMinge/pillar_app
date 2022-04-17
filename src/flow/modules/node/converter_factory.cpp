/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter_factory.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  ConverterFactory::ConverterFactory() : ConverterFactory({}, {}, {}) {}

  ConverterFactory::ConverterFactory(Creator creator, QString name, QIcon icon)
      : m_creator(std::move(creator)), m_icon(std::move(icon)),
        m_name(std::move(name))
  {}

  ConverterFactory::~ConverterFactory() = default;

  ConverterFactory::Creator ConverterFactory::getCreator() const
  {
    return m_creator;
  }

  QString ConverterFactory::getName() const { return m_name; }

  QIcon ConverterFactory::getIcon() const { return m_icon; }

  std::unique_ptr<TypeConverter> ConverterFactory::operator()() const
  {
    return m_creator();
  }

}// namespace node
