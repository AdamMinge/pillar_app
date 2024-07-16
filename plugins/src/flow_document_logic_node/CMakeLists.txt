# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/plugins/src/flow_document_logic_node)
set(include_root ${EGNITE_SOURCE_DIR}/plugins/include/flow_document_logic_node)

set(sources
    ${source_root}/logic_node_plugin.cpp
    ${source_root}/command/change_logic_node.cpp
    ${source_root}/event/logic_node_change_event.cpp
    ${source_root}/flow/logic_node_not.cpp
    ${source_root}/flow/logic_node_and.cpp
    ${source_root}/flow/logic_node_nand.cpp
    ${source_root}/flow/logic_node_or.cpp
    ${source_root}/flow/logic_node_xor.cpp
    ${source_root}/flow/logic_node_value.cpp
    ${source_root}/component/scene/item/logic_node_value_item.cpp
    ${source_root}/component/properties/logic_node_value_properties.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/logic_node_plugin.h
    ${include_root}/command/change_logic_node.h
    ${include_root}/event/logic_node_change_event.h
    ${include_root}/flow/logic_node_not.h
    ${include_root}/flow/logic_node_and.h
    ${include_root}/flow/logic_node_nand.h
    ${include_root}/flow/logic_node_or.h
    ${include_root}/flow/logic_node_xor.h
    ${include_root}/flow/logic_node_value.h
    ${include_root}/component/scene/item/logic_node_value_item.h
    ${include_root}/component/properties/logic_node_value_properties.h)
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
egnite_add_plugins(
  flow_document_logic_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  plugin::flow_document)

target_include_directories(
  flow_document_logic_node
  PUBLIC $<BUILD_INTERFACE:${include_root}>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${source_root})
# ----------------------------------------------------------------------- #
