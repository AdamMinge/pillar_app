# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/aegis/recorder_command)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/aegis/recorder_command)

set(sources
    ${source_root}/plugin.cpp ${source_root}/command/record.cpp
    ${source_root}/record/recorder.cpp ${source_root}/record/strategy.cpp)

set(includes
    ${include_root}/export.h ${include_root}/plugin.h
    ${include_root}/command/record.h ${include_root}/record/recorder.h
    ${include_root}/record/strategy.h)
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
