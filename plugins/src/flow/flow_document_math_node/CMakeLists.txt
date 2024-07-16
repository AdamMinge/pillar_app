# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/flow/flow_document_math_node)
set(include_root
    ${PILLAR_SOURCE_DIR}/plugins/include/flow/flow_document_math_node)

set(sources
    ${source_root}/math_node_plugin.cpp
    ${source_root}/command/change_math_node.cpp
    ${source_root}/event/math_node_change_event.cpp
    ${source_root}/flow/math_node_value.cpp
    ${source_root}/flow/math_node_addition.cpp
    ${source_root}/flow/math_node_division.cpp
    ${source_root}/flow/math_node_multiplication.cpp
    ${source_root}/flow/math_node_negation.cpp
    ${source_root}/flow/math_node_subtraction.cpp
    ${source_root}/flow/math_node_power.cpp
    ${source_root}/flow/math_node_square_root.cpp
    ${source_root}/flow/math_node_equal.cpp
    ${source_root}/flow/math_node_greater_equal.cpp
    ${source_root}/flow/math_node_greater.cpp
    ${source_root}/flow/math_node_lower_equal.cpp
    ${source_root}/flow/math_node_lower.cpp
    ${source_root}/flow/math_node_not_equal.cpp
    ${source_root}/component/scene/item/math_node_value_item.cpp
    ${source_root}/component/properties/math_node_value_properties.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/math_node_plugin.h
    ${include_root}/command/change_math_node.h
    ${include_root}/event/math_node_change_event.h
    ${include_root}/flow/math_node_value.h
    ${include_root}/flow/math_node_addition.h
    ${include_root}/flow/math_node_division.h
    ${include_root}/flow/math_node_multiplication.h
    ${include_root}/flow/math_node_negation.h
    ${include_root}/flow/math_node_subtraction.h
    ${include_root}/flow/math_node_power.h
    ${include_root}/flow/math_node_square_root.h
    ${include_root}/flow/math_node_equal.h
    ${include_root}/flow/math_node_greater_equal.h
    ${include_root}/flow/math_node_greater.h
    ${include_root}/flow/math_node_lower_equal.h
    ${include_root}/flow/math_node_lower.h
    ${include_root}/flow/math_node_not_equal.h
    ${include_root}/component/scene/item/math_node_value_item.h
    ${include_root}/component/properties/math_node_value_properties.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)
# ----------------------------------------------------------------------- #
# -------------------------- Create plugin shared lib ------------------- #
# ----------------------------------------------------------------------- #
pillar_add_plugins(
  flow_document_math_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  plugin::flow_document)

target_include_directories(
  flow_document_math_node
  PUBLIC $<BUILD_INTERFACE:${include_root}>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${source_root})
# ----------------------------------------------------------------------- #
