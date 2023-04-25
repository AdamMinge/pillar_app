# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/utils/stacked_widget)
set(include_root ${EGNITE_SOURCE_DIR}/include/utils/stacked_widget)
set(uis_root ${EGNITE_SOURCE_DIR}/uis/utils/stacked_widget)
set(resources_root ${EGNITE_SOURCE_DIR}/resources/utils/stacked_widget)

set(sources
    ${source_root}/stacked_widget_tree_model.cpp
    ${source_root}/stacked_widget_tree_delegate.cpp
    ${source_root}/stacked_widget_label.cpp ${source_root}/stacked_widget.cpp)

set(includes
    ${include_root}/export.h ${include_root}/stacked_widget_tree_model.h
    ${include_root}/stacked_widget_tree_delegate.h
    ${include_root}/stacked_widget_label.h ${include_root}/stacked_widget.h)

set(uis ${uis_root}/stacked_widget_label.ui)

set(resources ${resources_root}/stacked_widget.qrc)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration -------------------#
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${uis_root})
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries ---------------------#
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create utils shared lib ---------------------#
# ----------------------------------------------------------------------- #
egnite_add_utils(
  stacked_widget
  SOURCES
  ${sources}
  ${includes}
  ${uis}
  ${resources}
  DEPENDS_PRIVATE
  Qt6::Widgets)

target_include_directories(
  stacked_widget
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
