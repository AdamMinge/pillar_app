# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${PILLAR_SOURCE_DIR}/modules/src/pillar)
set(include_root ${PILLAR_SOURCE_DIR}/modules/include/pillar)
set(resource_root ${PILLAR_SOURCE_DIR}/modules/resource/pillar)

set(sources
    ${source_root}/application.cpp
    ${source_root}/command_line_parser.cpp
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
    ${source_root}/document/document_format.cpp
    ${source_root}/document/document_editor.cpp
    ${source_root}/document/new_document_widget.cpp
    ${source_root}/document/new_document_widget_factory.cpp
    ${source_root}/document/undo_dock.cpp
    ${source_root}/command/command.cpp
    ${source_root}/command/group_command.cpp)

set(includes
    ${include_root}/config.h
    ${include_root}/export.h
    ${include_root}/concept.h
    ${include_root}/application.h
    ${include_root}/command_line_parser.h
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
    ${include_root}/document/document_format.h
    ${include_root}/document/document_editor.h
    ${include_root}/document/new_document_widget.h
    ${include_root}/document/new_document_widget_factory.h
    ${include_root}/document/undo_dock.h
    ${include_root}/command/command.h
    ${include_root}/command/group_command.h)

set(resources ${resource_root}/pillar.qrc)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
set(QTILS_STATIC_LIBRARIES TRUE)

find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)
find_package(qtils REQUIRED COMPONENTS dialog serializer file_system)
# ----------------------------------------------------------------------- #
# -------------------------- Create pillar shared lib --------------------- #
# ----------------------------------------------------------------------- #
pillar_add_module(
  pillar
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Widgets
  DEPENDS_PRIVATE
  Qt6::Qml
  qtils::dialog
  qtils::serializer
  qtils::file_system)

target_include_directories(
  pillar
  PUBLIC $<BUILD_INTERFACE:${PILLAR_SOURCE_DIR}/modules/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${PILLAR_SOURCE_DIR}/modules/src/)

pillar_add_translations(
  pillar
  QM_DIR
  ${resource_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resource_root}/translations/pillar_pl.ts
  ${resource_root}/translations/pillar_en.ts)
# ----------------------------------------------------------------------- #
