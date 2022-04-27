/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/type_converter_factory.h"
#include "flow/libflow/node/type_converter.h"
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
    QString type_converter_id, std::unique_ptr<TypeConverterFactory> factory)
  {
    Q_ASSERT(!m_factories.contains(type_converter_id));
    m_factories.insert(
      std::make_pair(std::move(type_converter_id), std::move(factory)));
  }

  void
  TypeConverterFactories::unregisterFactory(const QString &type_converter_id)
  {
    Q_ASSERT(m_factories.contains(type_converter_id));
    m_factories.erase(type_converter_id);
  }

  QStringList TypeConverterFactories::getTypeConverterIds() const
  {
    QStringList keys;
    for (const auto &[key, _] : m_factories) keys << key;

    return keys;
  }

  TypeConverterFactory *
  TypeConverterFactories::getFactory(const QString &type_converter_id) const
  {
    if (!m_factories.contains(type_converter_id)) return nullptr;
    return m_factories.at(type_converter_id).get();
  }

  std::unique_ptr<TypeConverter>
  TypeConverterFactories::create(const QString &type_converter_id) const
  {
    if (!m_factories.contains(type_converter_id)) return nullptr;
    return m_factories.at(type_converter_id)->create();
  }

  QString TypeConverterFactories::getName() const { return m_name; }

  QIcon TypeConverterFactories::getIcon() const { return m_icon; }

}// namespace flow::node