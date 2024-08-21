# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/aegis/server)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/aegis/server)
set(ui_root ${PILLAR_SOURCE_DIR}/plugins/ui/aegis/server)
set(resource_root ${PILLAR_SOURCE_DIR}/plugins/resource/aegis/server)

set(sources ${source_root}/plugin.cpp
            ${source_root}/settings/server_settings_widget.cpp)

set(includes
    ${include_root}/export.h ${include_root}/plugin.h
    ${include_root}/resources.h
    ${include_root}/settings/server_settings_widget.h)

set(resources ${resource_root}/server.qrc)

set(uis ${ui_root}/settings/server_settings_widget.ui)
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
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(aegis REQUIRED COMPONENTS aegis)
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
  aegis::aegis)

target_include_directories(
  aegis_server
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src)

pillar_add_translations(
  aegis_server
  QM_DIR
  ${resource_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resource_root}/translations/server_pl.ts
  ${resource_root}/translations/server_en.ts)
# ----------------------------------------------------------------------- #
