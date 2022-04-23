/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/type_converter.h"
#include "flow/libflow/node/type_converter_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  /* -------------------------- TypeConverterFactory ------------------------ */

  TypeConverterFactory::TypeConverterFactory(QString name, QIcon icon)
      : m_name(std::move(name)), m_icon(std::move(icon))
  {}

  TypeConverterFactory::~TypeConverterFactory() = default;

  QString TypeConverterFactory::getName() const { return m_name; }

  QIcon TypeConverterFactory::getIcon() const { return m_icon; }

  /* -------------------------- TypeConverterFactories ---------------------- */

  TypeConverterFactories::TypeConverterFactories(QString name, QIcon icon)
      : m_name(std::move(name)), m_icon(std::move(icon))
  {}

  TypeConverterFactories::~TypeConverterFactories() = default;

  void TypeConverterFactories::registerFactory(
    QString node_id, std::unique_ptr<TypeConverterFactory> factory)
  {
    Q_ASSERT(!m_factories.contains(node_id));
    m_factories.insert(std::make_pair(std::move(node_id), std::move(factory)));
  }

  void TypeConverterFactories::unregisterFactory(const QString &node_id)
  {
    Q_ASSERT(m_factories.contains(node_id));
    m_factories.erase(node_id);
  }

  std::unique_ptr<TypeConverter>
  TypeConverterFactories::create(const QString &node_id) const
  {
    if (!m_factories.contains(node_id)) return nullptr;
    return m_factories.at(node_id)->create();
  }

  QString TypeConverterFactories::getName() const { return m_name; }

  QIcon TypeConverterFactories::getIcon() const { return m_icon; }

}// namespace flow::node