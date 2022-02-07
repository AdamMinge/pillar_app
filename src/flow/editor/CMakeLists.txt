# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/editor)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/editor)
set(uis_root ${FLOW_SOURCE_DIR}/uis/flow/editor)
set(resources_root ${FLOW_SOURCE_DIR}/resources)

set(sources
        ${source_root}/main.cpp
        ${source_root}/main_window.cpp
        ${source_root}/language_manager.cpp
        ${source_root}/style_manager.cpp
        ${source_root}/action_manager.cpp
        ${source_root}/plugin_manager.cpp
        ${source_root}/preferences_manager.cpp
        ${source_root}/logging_manager.cpp
        ${source_root}/issue.cpp
        ${source_root}/about_dialog.cpp
        ${source_root}/settings_dialog.cpp
        ${source_root}/console_dock.cpp
        ${source_root}/issue_dock.cpp

        ${source_root}/project/project.cpp
        ${source_root}/project/project_manager.cpp
        ${source_root}/project/project_session.cpp
        ${source_root}/project/project_window.cpp
        ${source_root}/project/no_project_window.cpp
        ${source_root}/project/new_project_dialog.cpp
        ${source_root}/project/project_dock.cpp
        ${source_root}/project/recent_project_list_model.cpp
        ${source_root}/project/recent_project_list_delegate.cpp
        ${source_root}/project/project_format_pro.cpp
        ${source_root}/project/project_writer.cpp
        ${source_root}/project/project_reader.cpp

        ${source_root}/document/document.cpp
        ${source_root}/document/document_manager.cpp
        ${source_root}/document/new_document_dialog.cpp
        ${source_root}/document/undo_dock.cpp
        ${source_root}/document/no_document_widget.cpp
        ${source_root}/document/document_type_list_model.cpp
        ${source_root}/document/document_type_list_delegate.cpp

        ${source_root}/document/flow/new_flow_document_widget.cpp
        ${source_root}/document/flow/flow_document.cpp
        ${source_root}/document/flow/flow_editor.cpp
        ${source_root}/document/flow/flow_scene.cpp
        ${source_root}/document/flow/flow_view.cpp
        ${source_root}/document/flow/flow_document_format.cpp
        ${source_root}/document/flow/flow_document_format_flow.cpp
        ${source_root}/document/flow/flow_document_reader.cpp
        ${source_root}/document/flow/flow_document_writer.cpp

        ${source_root}/commands/command.cpp
        ${source_root}/commands/group_command.cpp)

set(includes
        ${include_root}/main_window.h
        ${include_root}/language_manager.h
        ${include_root}/style_manager.h
        ${include_root}/action_manager.h
        ${include_root}/plugin_manager.h
        ${include_root}/preferences_manager.h
        ${include_root}/logging_manager.h
        ${include_root}/issue.h
        ${include_root}/about_dialog.h
        ${include_root}/settings_dialog.h
        ${include_root}/console_dock.h
        ${include_root}/issue_dock.h
        ${include_root}/format_helper.h

        ${include_root}/project/project.h
        ${include_root}/project/project_manager.h
        ${include_root}/project/project_session.h
        ${include_root}/project/project_window.h
        ${include_root}/project/no_project_window.h
        ${include_root}/project/new_project_dialog.h
        ${include_root}/project/project_dock.h
        ${include_root}/project/recent_project_list_model.h
        ${include_root}/project/recent_project_list_delegate.h
        ${include_root}/project/project_format_pro.h
        ${include_root}/project/project_writer.h
        ${include_root}/project/project_reader.h

        ${include_root}/document/document.h
        ${include_root}/document/document_manager.h
        ${include_root}/document/new_document_dialog.h
        ${include_root}/document/undo_dock.h
        ${include_root}/document/no_document_widget.h
        ${include_root}/document/document_type_list_model.h
        ${include_root}/document/document_type_list_delegate.h

        ${include_root}/document/flow/new_flow_document_widget.h
        ${include_root}/document/flow/flow_document.h
        ${include_root}/document/flow/flow_editor.h
        ${include_root}/document/flow/flow_scene.h
        ${include_root}/document/flow/flow_view.h
        ${include_root}/document/flow/flow_document_format.h
        ${include_root}/document/flow/flow_document_format_flow.h
        ${include_root}/document/flow/flow_document_reader.h
        ${include_root}/document/flow/flow_document_writer.h

        ${include_root}/commands/command.h
        ${include_root}/commands/group_command.h)

set(resources
        ${resources_root}/flow-editor-translations.qrc
        ${resources_root}/flow-editor-images.qrc)

set(uis
        ${uis_root}/main_window.ui
        ${uis_root}/about_dialog.ui
        ${uis_root}/settings_dialog.ui

        ${uis_root}/project/no_project_window.ui
        ${uis_root}/project/project_window.ui

        ${uis_root}/document/new_document_dialog.ui
        ${uis_root}/document/new_flow_document_widget.ui
        ${uis_root}/document/no_document_widget.ui)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Qt libraries configuration ------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${uis_root})
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# -------------------------------------------------------------------------------------------------- #
# ------------------------------------ create engine editor ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
flow_add_application(editor
        SOURCES ${sources} ${includes} ${uis} ${resources}
        DEPENDS
        Qt6::Widgets
        flow::api
        utils::pointer_cast
        utils::dialog
        utils::dpi
        utils::file_system_watcher
        utils::line_edit
        utils::property_browser
        utils::view
        utils::archive
        utils::widget)

flow_add_translations(editor
        QM_DIR ${resources_root}/translations/
        INCLUDES ${include_root}
        SOURCES ${source_root}
        TS_FILES
        ${resources_root}/translations/flow-editor_pl.ts
        ${resources_root}/translations/flow-editor_en.ts)
# -------------------------------------------------------------------------------------------------- #
