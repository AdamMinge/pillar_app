# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/apps/src/editor)
set(include_root ${PILLAR_SOURCE_DIR}/apps/include/editor)
set(ui_root ${PILLAR_SOURCE_DIR}/apps/ui/editor)
set(resource_root ${PILLAR_SOURCE_DIR}/apps/resource/editor)

set(sources
    ${source_root}/main.cpp
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
    ${ui_root}/main_window.ui
    ${ui_root}/issue_dock.ui
    ${ui_root}/about_dialog.ui
    ${ui_root}/settings/settings_dialog.ui
    ${ui_root}/settings/appearance_settings_widget.ui
    ${ui_root}/settings/general_settings_widget.ui
    ${ui_root}/settings/plugin_settings_widget.ui
    ${ui_root}/settings/shortcuts_settings_widget.ui
    ${ui_root}/project/no_project_window.ui
    ${ui_root}/project/project_window.ui
    ${ui_root}/project/new_project_dialog.ui
    ${ui_root}/document/new_document_dialog.ui
    ${ui_root}/document/no_document_widget.ui)

set(resources ${resource_root}/editor.qrc)
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
find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)
find_package(
  qtils REQUIRED
  COMPONENTS action
             color
             pointer
             container
             dialog
             dpi
             file_system
             line_edit
             property_browser
             view
             widget
             stacked_widget
             serializer)
# ----------------------------------------------------------------------- #
# ---------------------------- Create app editor ------------------------ #
# ----------------------------------------------------------------------- #
pillar_add_application(
  editor
  SOURCES
  ${sources}
  ${includes}
  ${uis}
  ${resources}
  DEPENDS
  Qt6::Widgets
  Qt6::Qml
  pillar::pillar
  DEPENDS_PRIVATE
  qtils::action
  qtils::color
  qtils::pointer
  qtils::container
  qtils::dialog
  qtils::dpi
  qtils::file_system
  qtils::line_edit
  qtils::property_browser
  qtils::view
  qtils::widget
  qtils::stacked_widget
  qtils::serializer)

target_include_directories(
  editor
  PUBLIC $<BUILD_INTERFACE:${include_root}>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${source_root})

pillar_add_translations(
  editor
  QM_DIR
  ${resource_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resource_root}/translations/editor_pl.ts
  ${resource_root}/translations/editor_en.ts)
# ----------------------------------------------------------------------- #
