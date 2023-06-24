# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root
    ${EGNITE_SOURCE_DIR}/src/plugins/flow_document/extensions/layer/shape)
set(include_root
    ${EGNITE_SOURCE_DIR}/include/plugins/flow_document/extensions/layer/shape)

set(sources ${source_root}/shape_layer_plugin.cpp)

set(includes ${include_root}/export.h ${include_root}/shape_layer_plugin.h)
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
  shape_layer
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  flow_document)

target_include_directories(
  shape_layer
  PUBLIC $<BUILD_INTERFACE:${include_root}>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${source_root})
# ----------------------------------------------------------------------- #
