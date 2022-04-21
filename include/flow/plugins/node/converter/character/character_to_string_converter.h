#ifndef PLUGIN_FLOW_CHARACTER_TO_STRING_CONVERTER_H
#define PLUGIN_FLOW_CHARACTER_TO_STRING_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class CHARACTER_CONVERTER_API CharacterToStringConverter : public flow::node::TypeConverter
{
public:
  explicit CharacterToStringConverter() = default;
  ~CharacterToStringConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_CHARACTER_TO_STRING_CONVERTER_H
