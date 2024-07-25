# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/aegis/aegis/recorder_command)
set(include_root
    ${PILLAR_SOURCE_DIR}/plugins/include/aegis/aegis/recorder_commandd)

set(sources ${source_root}/plugin.cpp ${source_root}/command/recorder.cpp)

set(includes ${include_root}/export.h ${include_root}/plugin.h
             ${include_root}/command/recorder.h)
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
  aegis_recorder_commandd
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Core
  Qt6::Widgets
  plugin::aegis_server)

target_include_directories(
  aegis_recorder_commandd
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)
# ----------------------------------------------------------------------- #
