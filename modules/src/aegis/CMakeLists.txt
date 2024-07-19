# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/modules/src/aegis)
set(include_root ${PILLAR_SOURCE_DIR}/modules/include/aegis)
set(resource_root ${PILLAR_SOURCE_DIR}/modules/resource/aegis)

set(sources
    ${source_root}/client.cpp ${source_root}/server.cpp
    ${source_root}/serializer.cpp ${source_root}/command/command.cpp
    ${source_root}/command/recorder.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/client.h
    ${include_root}/server.h
    ${include_root}/serializer.h
    ${include_root}/result.h
    ${include_root}/command/response.h
    ${include_root}/command/command.h
    ${include_root}/command/recorder.h)

set(resources ${resource_root}/aegis.qrc)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
find_package(qtils REQUIRED COMPONENTS serializer)
# ----------------------------------------------------------------------- #
# -------------------------- Create pillar shared lib --------------------- #
# ----------------------------------------------------------------------- #
pillar_add_module(
  aegis
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Widgets
  Qt6::Network
  DEPENDS_PRIVATE
  qtils::serializer)

target_include_directories(
  aegis
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/modules/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/modules/src/)

pillar_add_translations(
  aegis
  QM_DIR
  ${resource_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resource_root}/translations/aegis_pl.ts
  ${resource_root}/translations/aegis_en.ts)
# ----------------------------------------------------------------------- #
