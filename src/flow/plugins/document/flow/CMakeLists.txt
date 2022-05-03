# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/plugins/document/flow)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/plugins/document/flow)
set(uis_root ${FLOW_SOURCE_DIR}/uis/flow/plugins/document/flow)
set(resources_root ${FLOW_SOURCE_DIR}/resources)

set(sources
        ${source_root}/flow_document.cpp
        ${source_root}/flow_document_format.cpp
        ${source_root}/flow_document_format_flow.cpp
        ${source_root}/flow_document_plugin.cpp
        ${source_root}/flow_document_reader.cpp
        ${source_root}/flow_document_writer.cpp
        ${source_root}/flow_editor.cpp
        ${source_root}/flow_script_module.cpp
        ${source_root}/new_flow_document_widget.cpp

        ${source_root}/command/add_remove_node.cpp

        ${source_root}/component/node/flow_nodes_dock.cpp
        ${source_root}/component/node/flow_nodes_tree_delegate.cpp
        ${source_root}/component/node/flow_nodes_tree_model.cpp

        ${source_root}/component/scene/flow_node_geometry.cpp
        ${source_root}/component/scene/flow_node_item.cpp
        ${source_root}/component/scene/flow_node_painter.cpp
        ${source_root}/component/scene/flow_scene.cpp
        ${source_root}/component/scene/flow_view.cpp

        ${source_root}/component/tool/flow_abstract_tool.cpp
        ${source_root}/component/tool/selection_rectangle.cpp
        ${source_root}/component/tool/flow_selection_tool.cpp
        ${source_root}/component/tool/flow_tools_bar.cpp

        ${source_root}/component/type_converter/flow_type_converters_dock.cpp
        ${source_root}/component/type_converter/flow_type_converters_tree_delegate.cpp
        ${source_root}/component/type_converter/flow_type_converters_tree_model.cpp)

set(includes
        ${include_root}/export.h
        ${include_root}/flow_document.h
        ${include_root}/flow_document_format.h
        ${include_root}/flow_document_format_flow.h
        ${include_root}/flow_document_plugin.h
        ${include_root}/flow_document_reader.h
        ${include_root}/flow_document_writer.h
        ${include_root}/flow_editor.h
        ${include_root}/flow_script_module.h
        ${include_root}/new_flow_document_widget.h

        ${include_root}/command/add_remove_node.h

        ${include_root}/component/node/flow_nodes_dock.h
        ${include_root}/component/node/flow_nodes_tree_delegate.h
        ${include_root}/component/node/flow_nodes_tree_model.h

        ${include_root}/component/scene/flow_node_geometry.h
        ${include_root}/component/scene/flow_node_item.h
        ${include_root}/component/scene/flow_node_painter.h
        ${include_root}/component/scene/flow_scene.h
        ${include_root}/component/scene/flow_view.h

        ${include_root}/component/tool/flow_abstract_tool.h
        ${include_root}/component/tool/flow_selection_tool.h
        ${include_root}/component/tool/flow_tools_bar.h
        ${include_root}/component/tool/selection_rectangle.h

        ${include_root}/component/type_converter/flow_type_converters_dock.h
        ${include_root}/component/type_converter/flow_type_converters_tree_delegate.h
        ${include_root}/component/type_converter/flow_type_converters_tree_model.h)

set(resources
        ${resources_root}/plugin_document_flow_images.qrc)

set(uis
        ${uis_root}/new_flow_document_widget.ui
        ${uis_root}/flow_converters_dock.ui
        ${uis_root}/flow_nodes_dock.ui)
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
# ------------------------------------ Create utils shared lib ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
flow_add_plugins(flow_document
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS_PRIVATE Qt6::Widgets flow::lib_flow)
# -------------------------------------------------------------------------------------------------- #
