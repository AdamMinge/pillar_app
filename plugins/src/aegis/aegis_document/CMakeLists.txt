# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/plugins/src/aegis/aegis_document)
set(include_root ${PILLAR_SOURCE_DIR}/plugins/include/aegis/aegis_document)
set(ui_root ${PILLAR_SOURCE_DIR}/plugins/ui/aegis/aegis_document)
set(resource_root ${PILLAR_SOURCE_DIR}/plugins/resource/aegis/aegis_document)

set(sources ${source_root}/aegis_document_plugin.cpp)

set(includes ${include_root}/export.h ${include_root}/resources.h
             ${include_root}/aegis_document_plugin.h)

set(resources ${resource_root}/aegis_document.qrc)

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
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Qml)
# ----------------------------------------------------------------------- #
# -------------------------- Create plugin shared lib ------------------- #
# ----------------------------------------------------------------------- #
pillar_add_plugins(
  aegis_document
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Core
  Qt6::Widgets
  pillar::pillar
  pillar::aegis)

target_include_directories(
  aegis_document
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/plugins/include/aegis>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/plugins/src/aegis)

pillar_add_translations(
  aegis_document
  QM_DIR
  ${resource_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resource_root}/translations/aegis_document_pl.ts
  ${resource_root}/translations/aegis_document_en.ts)
# ----------------------------------------------------------------------- #
