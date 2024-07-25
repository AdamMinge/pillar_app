# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/flow/logic_node)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/flow/logic_node)

set(sources
    ${source_root}/plugin.cpp
    ${source_root}/command/change_node_value.cpp
    ${source_root}/event/node_value_change_event.cpp
    ${source_root}/flow/not.cpp
    ${source_root}/flow/and.cpp
    ${source_root}/flow/nand.cpp
    ${source_root}/flow/or.cpp
    ${source_root}/flow/xor.cpp
    ${source_root}/flow/value.cpp
    ${source_root}/component/scene/item/node_value_item.cpp
    ${source_root}/component/properties/node_value_properties.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/plugin.h
    ${include_root}/command/change_node_value.h
    ${include_root}/event/node_value_change_event.h
    ${include_root}/flow/not.h
    ${include_root}/flow/and.h
    ${include_root}/flow/nand.h
    ${include_root}/flow/or.h
    ${include_root}/flow/xor.h
    ${include_root}/flow/value.h
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
find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)
# ----------------------------------------------------------------------- #
# -------------------------- Create plugin shared lib ------------------- #
# ----------------------------------------------------------------------- #
pillar_add_plugins(
  flow_logic_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  plugin::flow_document)

target_include_directories(
  flow_logic_node
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)
# ----------------------------------------------------------------------- #
