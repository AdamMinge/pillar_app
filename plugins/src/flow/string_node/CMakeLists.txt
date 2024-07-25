# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/flow/string_node)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/flow/string_node)

set(sources
    ${source_root}/plugin.cpp
    ${source_root}/command/change_node_value.cpp
    ${source_root}/event/node_value_change_event.cpp
    ${source_root}/flow/value.cpp
    ${source_root}/flow/contains.cpp
    ${source_root}/flow/count.cpp
    ${source_root}/flow/equal.cpp
    ${source_root}/flow/insert.cpp
    ${source_root}/flow/lower.cpp
    ${source_root}/flow/mid.cpp
    ${source_root}/flow/not_equal.cpp
    ${source_root}/flow/remove.cpp
    ${source_root}/flow/replace.cpp
    ${source_root}/flow/reverse.cpp
    ${source_root}/flow/upper.cpp
    ${source_root}/component/scene/item/node_value_item.cpp
    ${source_root}/component/properties/node_value_properties.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/plugin.h
    ${include_root}/command/change_node_value.h
    ${include_root}/event/node_value_change_event.h
    ${include_root}/flow/contains.h
    ${include_root}/flow/count.h
    ${include_root}/flow/equal.h
    ${include_root}/flow/insert.h
    ${include_root}/flow/lower.h
    ${include_root}/flow/mid.h
    ${include_root}/flow/not_equal.h
    ${include_root}/flow/remove.h
    ${include_root}/flow/replace.h
    ${include_root}/flow/reverse.h
    ${include_root}/flow/upper.h
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
  flow_string_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  plugin::flow_document)

target_include_directories(
  flow_string_node
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)
# ----------------------------------------------------------------------- #
