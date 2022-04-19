#ifndef FLOW_CHARACTER_TO_BOOLEAN_CONVERTER_H
#define FLOW_CHARACTER_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class CHARACTER_CONVERTER_API CharacterToBooleanConverter : public flow::node::TypeConverter
{
public:
  explicit CharacterToBooleanConverter() = default;
  ~CharacterToBooleanConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//FLOW_CHARACTER_TO_BOOLEAN_CONVERTER_H
