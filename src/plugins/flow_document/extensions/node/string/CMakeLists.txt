# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root
    ${EGNITE_SOURCE_DIR}/src/plugins/flow_document/extensions/node/string)
set(include_root
    ${EGNITE_SOURCE_DIR}/include/plugins/flow_document/extensions/node/string)

set(sources
    ${source_root}/string_node_value.cpp
    ${source_root}/string_node_contains.cpp
    ${source_root}/string_node_count.cpp
    ${source_root}/string_node_equal.cpp
    ${source_root}/string_node_insert.cpp
    ${source_root}/string_node_lower.cpp
    ${source_root}/string_node_mid.cpp
    ${source_root}/string_node_not_equal.cpp
    ${source_root}/string_node_remove.cpp
    ${source_root}/string_node_replace.cpp
    ${source_root}/string_node_reverse.cpp
    ${source_root}/string_node_upper.cpp
    ${source_root}/string_node_plugin.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/string_node_contains.h
    ${include_root}/string_node_count.h
    ${include_root}/string_node_equal.h
    ${include_root}/string_node_insert.h
    ${include_root}/string_node_lower.h
    ${include_root}/string_node_mid.h
    ${include_root}/string_node_not_equal.h
    ${include_root}/string_node_remove.h
    ${include_root}/string_node_replace.h
    ${include_root}/string_node_reverse.h
    ${include_root}/string_node_upper.h
    ${include_root}/string_node_value.h
    ${include_root}/string_node_plugin.h)
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
egnite_add_plugins(
  string_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  flow_document)

target_include_directories(
  string_node
  PUBLIC $<BUILD_INTERFACE:${include_root}>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${source_root})
# ----------------------------------------------------------------------- #
