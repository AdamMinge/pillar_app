# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/egnite)
set(include_root ${EGNITE_SOURCE_DIR}/include/egnite)
set(resources_root ${EGNITE_SOURCE_DIR}/resources/egnite)

set(sources
    ${source_root}/plugin.cpp
    ${source_root}/logging_manager.cpp
    ${source_root}/script_manager.cpp
    ${source_root}/script_module.cpp
    ${source_root}/action_manager.cpp
    ${source_root}/file_format.cpp
    ${source_root}/plugin_interface.cpp
    ${source_root}/preferences_manager.cpp
    ${source_root}/style_manager.cpp
    ${source_root}/plugin_manager.cpp
    ${source_root}/language_manager.cpp
    ${source_root}/language_translator.cpp
    ${source_root}/issue_manager.cpp
    ${source_root}/issue.cpp
    ${source_root}/settings/settings_widget.cpp
    ${source_root}/settings/settings_widget_factory.cpp
    ${source_root}/project/project.cpp
    ${source_root}/project/project_format.cpp
    ${source_root}/project/project_manager.cpp
    ${source_root}/document/document.cpp
    ${source_root}/document/document_manager.cpp
    ${source_root}/document/document_editor.cpp
    ${source_root}/document/document_format.cpp
    ${source_root}/document/new_document_widget.cpp
    ${source_root}/document/new_document_widget_factory.cpp
    ${source_root}/document/undo_dock.cpp
    ${source_root}/command/command.cpp
    ${source_root}/command/group_command.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/concept.h
    ${include_root}/action_manager.h
    ${include_root}/file_format.h
    ${include_root}/format_helper.h
    ${include_root}/issue.h
    ${include_root}/issue_manager.h
    ${include_root}/language_manager.h
    ${include_root}/language_translator.h
    ${include_root}/logging_manager.h
    ${include_root}/plugin.h
    ${include_root}/plugin_listener.h
    ${include_root}/plugin_interface.h
    ${include_root}/plugin_manager.h
    ${include_root}/preferences_manager.h
    ${include_root}/script_manager.h
    ${include_root}/script_module.h
    ${include_root}/style_manager.h
    ${include_root}/settings/settings_widget.h
    ${include_root}/settings/settings_widget_factory.h
    ${include_root}/project/project.h
    ${include_root}/project/project_format.h
    ${include_root}/project/project_manager.h
    ${include_root}/document/document.h
    ${include_root}/document/document_manager.h
    ${include_root}/document/document_editor.h
    ${include_root}/document/document_format.h
    ${include_root}/document/new_document_widget.h
    ${include_root}/document/new_document_widget_factory.h
    ${include_root}/document/undo_dock.h
    ${include_root}/command/command.h
    ${include_root}/command/group_command.h)

set(resources ${resources_root}/egnite.qrc)
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
# -------------------------- Create egnite shared lib --------------------- #
# ----------------------------------------------------------------------- #
egnite_add_module(
  egnite
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Widgets
  Qt6::Qml
  DEPENDS_PRIVATE
  utils::dialog
  utils::serializer
  utils::file_system)

target_include_directories(
  egnite
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/)

egnite_add_translations(
  egnite
  QM_DIR
  ${resources_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resources_root}/translations/egnite_pl.ts
  ${resources_root}/translations/egnite_en.ts)
# ----------------------------------------------------------------------- #
