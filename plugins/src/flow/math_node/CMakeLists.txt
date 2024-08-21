# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/flow/math_node)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/flow/math_node)

set(sources
    ${source_root}/plugin.cpp
    ${source_root}/command/change_node_value.cpp
    ${source_root}/event/node_value_change_event.cpp
    ${source_root}/flow/value.cpp
    ${source_root}/flow/addition.cpp
    ${source_root}/flow/division.cpp
    ${source_root}/flow/multiplication.cpp
    ${source_root}/flow/negation.cpp
    ${source_root}/flow/subtraction.cpp
    ${source_root}/flow/power.cpp
    ${source_root}/flow/square_root.cpp
    ${source_root}/flow/equal.cpp
    ${source_root}/flow/greater_equal.cpp
    ${source_root}/flow/greater.cpp
    ${source_root}/flow/lower_equal.cpp
    ${source_root}/flow/lower.cpp
    ${source_root}/flow/not_equal.cpp
    ${source_root}/component/scene/item/node_value_item.cpp
    ${source_root}/component/properties/node_value_properties.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/plugin.h
    ${include_root}/command/change_node_value.h
    ${include_root}/event/node_value_change_event.h
    ${include_root}/flow/value.h
    ${include_root}/flow/addition.h
    ${include_root}/flow/division.h
    ${include_root}/flow/multiplication.h
    ${include_root}/flow/negation.h
    ${include_root}/flow/subtraction.h
    ${include_root}/flow/power.h
    ${include_root}/flow/square_root.h
    ${include_root}/flow/equal.h
    ${include_root}/flow/greater_equal.h
    ${include_root}/flow/greater.h
    ${include_root}/flow/lower_equal.h
    ${include_root}/flow/lower.h
    ${include_root}/flow/not_equal.h
    ${include_root}/component/scene/item/node_value_item.h
    ${include_root}/component/properties/node_value_properties.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create plugin shared lib ------------------- #
# ----------------------------------------------------------------------- #
pillar_add_plugins(
  flow_math_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  plugin::flow_document)

target_include_directories(
  flow_math_node
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)
# ----------------------------------------------------------------------- #
