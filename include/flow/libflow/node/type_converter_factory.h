#ifndef FLOW_TYPE_CONVERTER_FACTORY_H
#define FLOW_TYPE_CONVERTER_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class TypeConverter;

  class LIB_FLOW_API TypeConverterFactory
  {
  public:
    explicit TypeConverterFactory(QString name, QIcon icon);
    virtual ~TypeConverterFactory();

    [[nodiscard]] virtual std::unique_ptr<TypeConverter> create() const = 0;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

  private:
    QString m_name;
    QIcon m_icon;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, TypeConverter>
  class LIB_FLOW_API BaseTypeConverterFactory : public TypeConverterFactory
  {
  public:
    explicit BaseTypeConverterFactory(QString name, QIcon icon);

    [[nodiscard]] std::unique_ptr<TypeConverter> create() const override;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, TypeConverter>
  BaseTypeConverterFactory<TYPE>::BaseTypeConverterFactory(
    QString name, QIcon icon)
      : TypeConverterFactory(name, icon)
  {}

  template<typename TYPE>
  requires std::derived_from<TYPE, TypeConverter> std::unique_ptr<TypeConverter>
  BaseTypeConverterFactory<TYPE>::create()
  const { return std::make_unique<TYPE>(); }

  class LIB_FLOW_API TypeConverterFactories : public QObject
  {
    Q_OBJECT

  public:
    explicit TypeConverterFactories(QString name, QIcon icon);
    ~TypeConverterFactories() override;

    void registerFactory(
      QString type_converter_id, std::unique_ptr<TypeConverterFactory> factory);
    void unregisterFactory(const QString &type_converter_id);

    [[nodiscard]] QStringList getTypeConverterIds() const;
    [[nodiscard]] TypeConverterFactory *
    getFactory(const QString &type_converter_id) const;

    [[nodiscard]] virtual std::unique_ptr<TypeConverter>
    create(const QString &type_converter_id) const;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

  private:
    std::map<QString, std::unique_ptr<TypeConverterFactory>> m_factories;
    QString m_name;
    QIcon m_icon;
  };

}// namespace flow::node

Q_DECLARE_INTERFACE(
  flow::node::TypeConverterFactories, "org.flow.TypeConverterFactories")

#endif//FLOW_TYPE_CONVERTER_FACTORY_H
