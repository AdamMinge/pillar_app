# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/aegis/object_command)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/aegis/object_command)

set(sources
    ${source_root}/plugin.cpp ${source_root}/command/invoke_method.cpp
    ${source_root}/command/set_property.cpp ${source_root}/command/dump.cpp)

set(includes
    ${include_root}/export.h ${include_root}/plugin.h
    ${include_root}/command/invoke_method.h
    ${include_root}/command/set_property.h ${include_root}/command/dump.h)
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
  aegis_object_command
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Core
  Qt6::Widgets
  plugin::aegis_server)

target_include_directories(
  aegis_object_command
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)
# ----------------------------------------------------------------------- #
