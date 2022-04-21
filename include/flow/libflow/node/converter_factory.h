#ifndef FLOW_CONVERTER_FACTORY_H
#define FLOW_CONVERTER_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class TypeConverter;

  class LIB_FLOW_API ConverterFactory
  {
  public:
    explicit ConverterFactory(QString name, QIcon icon);
    virtual ~ConverterFactory();

    [[nodiscard]] virtual std::unique_ptr<TypeConverter> create() const = 0;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

  private:
    QString m_name;
    QIcon m_icon;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, TypeConverter>
  class LIB_FLOW_API BaseConverterFactory : public ConverterFactory
  {
  public:
    explicit BaseConverterFactory(QString name, QIcon icon);

    [[nodiscard]] std::unique_ptr<TypeConverter> create() const override;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, TypeConverter>
  BaseConverterFactory<TYPE>::BaseConverterFactory(QString name, QIcon icon)
      : ConverterFactory(name, icon)
  {}

  template<typename TYPE>
  requires std::derived_from<TYPE, TypeConverter> std::unique_ptr<TypeConverter>
  BaseConverterFactory<TYPE>::create()
  const { return std::make_unique<TYPE>(); }

  class LIB_FLOW_API ConverterFactories : public QObject
  {
    Q_OBJECT

  public:
    explicit ConverterFactories(QString name, QIcon icon);
    ~ConverterFactories() override;

    void
    registerFactory(QString node_id, std::unique_ptr<ConverterFactory> factory);
    void unregisterFactory(const QString &node_id);

    [[nodiscard]] virtual std::unique_ptr<TypeConverter>
    create(const QString &node_id) const;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

  private:
    std::map<QString, std::unique_ptr<ConverterFactory>> m_factories;
    QString m_name;
    QIcon m_icon;
  };

}// namespace flow::node

Q_DECLARE_INTERFACE(
  flow::node::ConverterFactories, "org.flow.ConverterFactories")

#endif//FLOW_CONVERTER_FACTORY_H
