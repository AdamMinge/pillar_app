# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/flow/condition_node)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/flow/condition_node)

set(sources ${source_root}/plugin.cpp ${source_root}/flow/switcher.cpp
            ${source_root}/flow/dispatcher.cpp)

set(includes ${include_root}/export.h ${include_root}/plugin.h
             ${include_root}/flow/switcher.h ${include_root}/flow/dispatcher.h)
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
  flow_condition_node
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Core
  Qt6::Widgets
  plugin::flow_document)

target_include_directories(
  flow_condition_node
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)
# ----------------------------------------------------------------------- #
