#ifndef FLOW_TYPE_CONVERTER_PLUGIN_H
#define FLOW_TYPE_CONVERTER_PLUGIN_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_interface.h>
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class TypeConverter;
}

class INTEGER_CONVERTER_API TypeConverter : public flow::PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(flow::PluginInterface);
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

public:
  explicit TypeConverter();
  ~TypeConverter() override;

private:
  QScopedPointer<flow::node::TypeConverter> m_integer_to_boolean_converter;
  QScopedPointer<flow::node::TypeConverter> m_integer_to_character_converter;
  QScopedPointer<flow::node::TypeConverter> m_integer_to_floating_point_converter;
  QScopedPointer<flow::node::TypeConverter> m_integer_to_string_converter;
};

#endif//FLOW_TYPE_CONVERTER_PLUGIN_H
