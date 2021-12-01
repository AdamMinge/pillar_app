# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/tools/editor)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/tools/editor)
set(uis_root ${FLOW_SOURCE_DIR}/uis/flow/tools/editor)
set(resources_root ${FLOW_SOURCE_DIR}/resources)

set(sources
        ${source_root}/meta_types.cpp
        ${source_root}/main.cpp
        ${source_root}/main_window.cpp
        ${source_root}/language_manager.cpp
        ${source_root}/style_manager.cpp
        ${source_root}/action_manager.cpp
        ${source_root}/preferences_manager.cpp
        ${source_root}/logging_manager.cpp
        ${source_root}/issue.cpp
        ${source_root}/about_dialog.cpp

        ${source_root}/document/document.cpp
        ${source_root}/document/document_editor.cpp
        ${source_root}/document/document_manager.cpp
        ${source_root}/document/new_document_dialog.cpp
        ${source_root}/document/new_document_widget.cpp
        ${source_root}/document/new_flow_document_widget.cpp
        ${source_root}/document/flow_document.cpp
        ${source_root}/document/flow_editor.cpp
        ${source_root}/document/flow_scene.cpp
        ${source_root}/document/flow_view.cpp
        ${source_root}/document/undo_dock.cpp
        ${source_root}/document/no_document_widget.cpp
        ${source_root}/document/document_list_model.cpp
        ${source_root}/document/document_list_delegate.cpp
        ${source_root}/document/document_type_list_model.cpp
        ${source_root}/document/document_type_list_delegate.cpp
        ${source_root}/document/document_serializer.cpp
        ${source_root}/document/priv/document_serializer_impl.h
        ${source_root}/document/priv/document_serializer_impl.cpp
        ${source_root}/document/priv/json_document_serializer_impl.h
        ${source_root}/document/priv/json_document_serializer_impl.cpp

        ${source_root}/commands/command.cpp
        ${source_root}/commands/group_command.cpp)

set(includes
        ${include_root}/meta_types.h
        ${include_root}/main_window.h
        ${include_root}/language_manager.h
        ${include_root}/style_manager.h
        ${include_root}/action_manager.h
        ${include_root}/preferences_manager.h
        ${include_root}/logging_manager.h
        ${include_root}/issue.h
        ${include_root}/about_dialog.h

        ${include_root}/document/document.h
        ${include_root}/document/document_editor.h
        ${include_root}/document/document_manager.h
        ${include_root}/document/new_document_dialog.h
        ${include_root}/document/new_document_widget.h
        ${include_root}/document/new_flow_document_widget.h
        ${include_root}/document/flow_document.h
        ${include_root}/document/flow_editor.h
        ${include_root}/document/flow_scene.h
        ${include_root}/document/flow_view.h
        ${include_root}/document/undo_dock.h
        ${include_root}/document/document_serializer.h
        ${include_root}/document/no_document_widget.h
        ${include_root}/document/document_list_model.h
        ${include_root}/document/document_list_delegate.h
        ${include_root}/document/document_type_list_model.h
        ${include_root}/document/document_type_list_delegate.h

        ${include_root}/commands/command.h
        ${include_root}/commands/group_command.h)

set(resources
        ${resources_root}/flow-tools-editor-translations.qrc
        ${resources_root}/flow-tools-editor-images.qrc)

set(uis
        ${uis_root}/main_window.ui
        ${uis_root}/about_dialog.ui

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
flow_add_tool(flow-tools-editor
        SOURCES ${sources} ${includes} ${uis} ${resources}
        DEPENDS Qt6::Widgets tool::tools-shared engine::flow-engine)

flow_add_translations(flow-tools-editor
        QM_DIR ${resources_root}/translations/
        INCLUDES ${include_root}
        SOURCES ${source_root}
        TS_FILES
        ${resources_root}/translations/flow-tools-editor_pl.ts
        ${resources_root}/translations/flow-tools-editor_en.ts)
# -------------------------------------------------------------------------------------------------- #
