# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/utils/widget)
set(include_root ${EGNITE_SOURCE_DIR}/include/utils/widget)
set(uis_root ${EGNITE_SOURCE_DIR}/uis/utils/widget)

set(sources ${source_root}/name_and_path_filler.cpp
            ${source_root}/shortcut_selector.cpp)

set(includes ${include_root}/export.h ${include_root}/name_and_path_filler.h
             ${include_root}/shortcut_selector.h)

set(uis ${uis_root}/name_and_path_filler.ui)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${uis_root})
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create utils shared lib -------------------- #
# ----------------------------------------------------------------------- #
egnite_add_utils(
  widget
  SOURCES
  ${sources}
  ${includes}
  ${uis}
  DEPENDS
  Qt6::Widgets)

target_include_directories(
  widget
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
