/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/converter_factory.h"
#include "flow/libflow/node/type_converter.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  /* ---------------------------- ConverterFactory -------------------------- */

  ConverterFactory::ConverterFactory(QString name, QIcon icon)
      : m_name(std::move(name)), m_icon(std::move(icon))
  {}

  ConverterFactory::~ConverterFactory() = default;

  QString ConverterFactory::getName() const { return m_name; }

  QIcon ConverterFactory::getIcon() const { return m_icon; }

  /* ---------------------------- ConverterFactories ------------------------ */

  ConverterFactories::ConverterFactories(QString name, QIcon icon)
      : m_name(std::move(name)), m_icon(std::move(icon))
  {}

  ConverterFactories::~ConverterFactories() = default;

  void ConverterFactories::registerFactory(
    QString node_id, std::unique_ptr<ConverterFactory> factory)
  {
    Q_ASSERT(!m_factories.contains(node_id));
    m_factories.insert(std::make_pair(std::move(node_id), std::move(factory)));
  }

  void ConverterFactories::unregisterFactory(const QString &node_id)
  {
    Q_ASSERT(m_factories.contains(node_id));
    m_factories.erase(node_id);
  }

  std::unique_ptr<TypeConverter>
  ConverterFactories::create(const QString &node_id) const
  {
    if (!m_factories.contains(node_id)) return nullptr;
    return m_factories.at(node_id)->create();
  }

  QString ConverterFactories::getName() const { return m_name; }

  QIcon ConverterFactories::getIcon() const { return m_icon; }

}// namespace flow::node