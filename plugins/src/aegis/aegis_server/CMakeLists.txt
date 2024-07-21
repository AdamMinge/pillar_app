# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/aegis/aegis_server)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/aegis/aegis_server)
set(ui_root ${PILLAR_SOURCE_DIR}/plugins/ui/aegis/aegis_server)
set(resource_root ${PILLAR_SOURCE_DIR}/plugins/resource/aegis/aegis_server)

set(sources
    ${source_root}/aegis_server_plugin.cpp ${source_root}/client.cpp
    ${source_root}/server.cpp ${source_root}/serializer.cpp
    ${source_root}/command/command.cpp ${source_root}/command/recorder.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/aegis_server_plugin.h
    ${include_root}/client.h
    ${include_root}/server.h
    ${include_root}/serializer.h
    ${include_root}/response.h
    ${include_root}/resources.h
    ${include_root}/command/command.h
    ${include_root}/command/recorder.h)

set(resources ${resource_root}/aegis_server.qrc)

set(uis)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${ui_root})
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Qml)
find_package(qtils REQUIRED COMPONENTS serializer)
# ----------------------------------------------------------------------- #
# -------------------------- Create plugin shared lib ------------------- #
# ----------------------------------------------------------------------- #
pillar_add_plugins(
  aegis_server
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Core
  Qt6::Widgets
  Qt6::Network
  pillar::pillar
  qtils::serializer)

target_include_directories(
  aegis_server
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include/aegis>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src/aegis)

pillar_add_translations(
  aegis_server
  QM_DIR
  ${resource_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resource_root}/translations/aegis_server_pl.ts
  ${resource_root}/translations/aegis_server_en.ts)
# ----------------------------------------------------------------------- #
