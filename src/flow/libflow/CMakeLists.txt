# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/libflow)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/libflow)
set(resources_root ${FLOW_SOURCE_DIR}/resources)

set(sources
        ${source_root}/object.cpp
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
        ${source_root}/command/group_command.cpp

        ${source_root}/node/connection.cpp
        ${source_root}/node/node.cpp
        ${source_root}/node/pin.cpp
        ${source_root}/node/node_factory.cpp
        ${source_root}/node/type_converter_factory.cpp

        ${source_root}/node/base/boolean_node_data.cpp
        ${source_root}/node/base/character_node_data.cpp
        ${source_root}/node/base/floating_point_node_data.cpp
        ${source_root}/node/base/integer_node_data.cpp
        ${source_root}/node/base/string_node_data.cpp)

set(includes
        ${include_root}/export.h
        ${include_root}/object.h
        ${include_root}/action_manager.h
        ${include_root}/export.h
        ${include_root}/file_format.h
        ${include_root}/format_helper.h
        ${include_root}/issue.h
        ${include_root}/issue_manager.h
        ${include_root}/language_manager.h
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
        ${include_root}/command/group_command.h

        ${include_root}/node/connection.h
        ${include_root}/node/node.h
        ${include_root}/node/node_data.h
        ${include_root}/node/pin.h
        ${include_root}/node/type_converter.h
        ${include_root}/node/node_factory.h
        ${include_root}/node/type_converter_factory.h

        ${include_root}/node/base/boolean_node_data.h
        ${include_root}/node/base/character_node_data.h
        ${include_root}/node/base/floating_point_node_data.h
        ${include_root}/node/base/integer_node_data.h
        ${include_root}/node/base/string_node_data.h)

set(resources
        ${resources_root}/libflow_images.qrc)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Qt libraries configuration ------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)
# -------------------------------------------------------------------------------------------------- #
# ------------------------------------ Create utils shared lib ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
flow_add_module(lib_flow
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS_PRIVATE
        Qt6::Widgets
        Qt6::Qml
        utils::dialog
        utils::file_system_watcher)
# -------------------------------------------------------------------------------------------------- #
