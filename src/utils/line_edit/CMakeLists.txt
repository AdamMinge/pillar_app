# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/utils/line_edit)
set(include_root ${EGNITE_SOURCE_DIR}/include/utils/line_edit)
set(resources_root ${EGNITE_SOURCE_DIR}/resources/utils/line_edit)

set(sources
    ${source_root}/line_edit_with_history.cpp
    ${source_root}/file_browser_line_edit.cpp
    ${source_root}/dir_browser_line_edit.cpp)

set(includes
    ${include_root}/export.h ${include_root}/line_edit_with_history.h
    ${include_root}/file_browser_line_edit.h
    ${include_root}/dir_browser_line_edit.h)

set(resources ${resources_root}/line_edit.qrc)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration -------------------#
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries ---------------------#
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create utils shared lib ---------------------#
# ----------------------------------------------------------------------- #
egnite_add_utils(
  line_edit
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Widgets
  DEPENDS_PRIVATE
  utils::dialog)

target_include_directories(
  line_edit
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
