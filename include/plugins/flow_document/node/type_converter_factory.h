#ifndef FLOW_TYPE_CONVERTER_FACTORY_H
#define FLOW_TYPE_CONVERTER_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class TypeConverter;

class FLOW_DOCUMENT_API TypeConverterFactory {
 public:
  explicit TypeConverterFactory(QString name, QString type_converter_id);
  virtual ~TypeConverterFactory();

  [[nodiscard]] virtual std::unique_ptr<TypeConverter> create() const = 0;

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getTypeConverterId() const;

 private:
  QString m_name;
  QString m_type_converter_id;
};

template <typename TYPE>
requires std::derived_from<TYPE, TypeConverter>
class BaseTypeConverterFactory : public TypeConverterFactory {
 public:
  explicit BaseTypeConverterFactory(QString name, QString type_converter_id);

  [[nodiscard]] std::unique_ptr<TypeConverter> create() const override;
};

template <typename TYPE>
requires std::derived_from<TYPE, TypeConverter> BaseTypeConverterFactory<
    TYPE>::BaseTypeConverterFactory(QString name, QString type_converter_id)
    : TypeConverterFactory(std::move(name), std::move(type_converter_id)) {}

template <typename TYPE>
requires std::derived_from<TYPE, TypeConverter> std::unique_ptr<TypeConverter>
BaseTypeConverterFactory<TYPE>::create()
const { return std::make_unique<TYPE>(); }

class FLOW_DOCUMENT_API TypeConverterFactories : public QObject {
  Q_OBJECT

 public:
  explicit TypeConverterFactories(QString name);
  ~TypeConverterFactories() override;

  void registerFactory(std::unique_ptr<TypeConverterFactory> factory);
  void unregisterFactory(const QString &type_converter_id);

  [[nodiscard]] QStringList getTypeConverterIds() const;
  [[nodiscard]] TypeConverterFactory *getFactory(
      const QString &type_converter_id) const;

  [[nodiscard]] virtual std::unique_ptr<TypeConverter> create(
      const QString &type_converter_id) const;

  [[nodiscard]] QString getName() const;

 private:
  std::map<QString, std::unique_ptr<TypeConverterFactory>> m_factories;
  QString m_name;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::TypeConverterFactories,
                    "org.flow.TypeConverterFactories")

#endif  // FLOW_TYPE_CONVERTER_FACTORY_H
