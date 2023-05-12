# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/editor)
set(include_root ${EGNITE_SOURCE_DIR}/include/editor)
set(uis_root ${EGNITE_SOURCE_DIR}/uis/editor)
set(resources_root ${EGNITE_SOURCE_DIR}/resources/editor)

set(sources
    ${source_root}/main.cpp
    ${source_root}/command_line_parser.cpp
    ${source_root}/main_window.cpp
    ${source_root}/about_dialog.cpp
    ${source_root}/console_dock.cpp
    ${source_root}/issue_dock.cpp
    ${source_root}/issue_table_model.cpp
    ${source_root}/issue_table_filter_model.cpp
    ${source_root}/settings/settings_dialog.cpp
    ${source_root}/settings/settings_widget_tree_model.cpp
    ${source_root}/settings/general_settings_widget.cpp
    ${source_root}/settings/plugin_settings_widget.cpp
    ${source_root}/settings/shortcuts_settings_widget.cpp
    ${source_root}/settings/appearance_settings_widget.cpp
    ${source_root}/settings/plugin_list_model.cpp
    ${source_root}/settings/plugin_list_delegate.cpp
    ${source_root}/settings/shortcuts_table_model.cpp
    ${source_root}/settings/shortcuts_table_delegate.cpp
    ${source_root}/project/project_window.cpp
    ${source_root}/project/no_project_window.cpp
    ${source_root}/project/new_project_dialog.cpp
    ${source_root}/project/project_dock.cpp
    ${source_root}/project/recent_project_list_model.cpp
    ${source_root}/project/recent_project_list_delegate.cpp
    ${source_root}/project/project_format_pro.cpp
    ${source_root}/project/project_writer.cpp
    ${source_root}/project/project_reader.cpp
    ${source_root}/document/new_document_dialog.cpp
    ${source_root}/document/no_document_widget.cpp
    ${source_root}/document/new_document_widget_list_model.cpp
    ${source_root}/document/new_document_widget_list_delegate.cpp)

set(includes
    ${include_root}/resources.h
    ${include_root}/command_line_parser.h
    ${include_root}/main_window.h
    ${include_root}/about_dialog.h
    ${include_root}/console_dock.h
    ${include_root}/issue_dock.h
    ${include_root}/issue_table_model.h
    ${include_root}/issue_table_filter_model.h
    ${include_root}/settings/settings_dialog.h
    ${include_root}/settings/settings_widget_tree_model.h
    ${include_root}/settings/general_settings_widget.h
    ${include_root}/settings/plugin_settings_widget.h
    ${include_root}/settings/shortcuts_settings_widget.h
    ${include_root}/settings/appearance_settings_widget.h
    ${include_root}/settings/plugin_list_model.h
    ${include_root}/settings/plugin_list_delegate.h
    ${include_root}/settings/shortcuts_table_model.h
    ${include_root}/settings/shortcuts_table_delegate.h
    ${include_root}/project/project_window.h
    ${include_root}/project/no_project_window.h
    ${include_root}/project/new_project_dialog.h
    ${include_root}/project/project_dock.h
    ${include_root}/project/recent_project_list_model.h
    ${include_root}/project/recent_project_list_delegate.h
    ${include_root}/project/project_format_pro.h
    ${include_root}/project/project_writer.h
    ${include_root}/project/project_reader.h
    ${include_root}/document/new_document_dialog.h
    ${include_root}/document/no_document_widget.h
    ${include_root}/document/new_document_widget_list_model.h
    ${include_root}/document/new_document_widget_list_delegate.h)

set(uis
    ${uis_root}/main_window.ui
    ${uis_root}/issue_dock.ui
    ${uis_root}/about_dialog.ui
    ${uis_root}/settings/settings_dialog.ui
    ${uis_root}/settings/appearance_settings_widget.ui
    ${uis_root}/settings/general_settings_widget.ui
    ${uis_root}/settings/plugin_settings_widget.ui
    ${uis_root}/settings/shortcuts_settings_widget.ui
    ${uis_root}/project/no_project_window.ui
    ${uis_root}/project/project_window.ui
    ${uis_root}/project/new_project_dialog.ui
    ${uis_root}/document/new_document_dialog.ui
    ${uis_root}/document/no_document_widget.ui)

set(resources ${resources_root}/editor.qrc)
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
find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)
find_package(Boost 1.78 REQUIRED)
# ----------------------------------------------------------------------- #
# ---------------------------- Create app editor ------------------------ #
# ----------------------------------------------------------------------- #
egnite_add_application(
  editor
  SOURCES
  ${sources}
  ${includes}
  ${uis}
  ${resources}
  DEPENDS
  Qt6::Widgets
  Qt6::Qml
  egnite::egnite
  utils::action
  utils::color
  utils::pointer_cast
  utils::container
  utils::dialog
  utils::dpi
  utils::file_system
  utils::line_edit
  utils::property_browser
  utils::view
  utils::widget
  utils::stacked_widget)

target_include_directories(
  editor
  PUBLIC $<BUILD_INTERFACE:${include_root}>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${source_root})

egnite_add_translations(
  editor
  QM_DIR
  ${resources_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resources_root}/translations/editor_pl.ts
  ${resources_root}/translations/editor_en.ts)
# ----------------------------------------------------------------------- #
