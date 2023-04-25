# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/plugins/flow_document/)
set(include_root ${EGNITE_SOURCE_DIR}/include/plugins/flow_document)
set(uis_root ${EGNITE_SOURCE_DIR}/uis/plugins/flow_document)
set(resources_root ${EGNITE_SOURCE_DIR}/resources/plugins/flow_document)

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
    ${source_root}/event/change_event.cpp
    ${source_root}/event/objects_event.cpp
    ${source_root}/command/add_remove_node.cpp
    ${source_root}/command/move_object.cpp
    ${source_root}/flow/flow_object.cpp
    ${source_root}/flow/flow_node.cpp
    ${source_root}/flow/flow_pin.cpp
    ${source_root}/flow/flow_connection.cpp
    ${source_root}/flow/flow_node_factory.cpp
    ${source_root}/flow/flow_graph.cpp
    ${source_root}/component/node/flow_nodes_dock.cpp
    ${source_root}/component/node/flow_nodes_tree_delegate.cpp
    ${source_root}/component/node/flow_nodes_tree_model.cpp
    ${source_root}/component/scene/flow_node_geometry.cpp
    ${source_root}/component/scene/flow_node_painter.cpp
    ${source_root}/component/scene/flow_style_manager.cpp
    ${source_root}/component/scene/flow_style_writer.cpp
    ${source_root}/component/scene/flow_style_reader.cpp
    ${source_root}/component/scene/flow_style.cpp
    ${source_root}/component/scene/flow_node_graphics_item.cpp
    ${source_root}/component/scene/flow_graphics_item.cpp
    ${source_root}/component/scene/flow_scene.cpp
    ${source_root}/component/scene/flow_view.cpp
    ${source_root}/component/scene/flow_abstract_tool.cpp
    ${source_root}/component/scene/selection_rectangle.cpp
    ${source_root}/component/scene/flow_selection_tool.cpp
    ${source_root}/component/scene/flow_tools_bar.cpp)

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
    ${include_root}/event/change_event.h
    ${include_root}/event/objects_event.h
    ${include_root}/command/add_remove_node.h
    ${include_root}/command/move_object.h
    ${include_root}/flow/flow_object.h
    ${include_root}/flow/flow_node.h
    ${include_root}/flow/flow_pin.h
    ${include_root}/flow/flow_connection.h
    ${include_root}/flow/flow_node_factory.h
    ${include_root}/flow/flow_graph.h
    ${include_root}/component/node/flow_nodes_dock.h
    ${include_root}/component/node/flow_nodes_tree_delegate.h
    ${include_root}/component/node/flow_nodes_tree_model.h
    ${include_root}/component/scene/flow_node_geometry.h
    ${include_root}/component/scene/flow_node_painter.h
    ${include_root}/component/scene/flow_style_manager.h
    ${include_root}/component/scene/flow_style_writer.h
    ${include_root}/component/scene/flow_style_reader.h
    ${include_root}/component/scene/flow_style.h
    ${include_root}/component/scene/flow_node_graphics_item.h
    ${include_root}/component/scene/flow_graphics_item.h
    ${include_root}/component/scene/flow_scene.h
    ${include_root}/component/scene/flow_view.h
    ${include_root}/component/scene/flow_abstract_tool.h
    ${include_root}/component/scene/flow_selection_tool.h
    ${include_root}/component/scene/flow_tools_bar.h
    ${include_root}/component/scene/selection_rectangle.h)

set(resources ${resources_root}/flow_document.qrc)

set(uis ${uis_root}/new_flow_document_widget.ui ${uis_root}/flow_nodes_dock.ui)
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
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create plugin shared lib ------------------- #
# ----------------------------------------------------------------------- #
egnite_add_plugins(
  flow_document
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS_PRIVATE
  Qt6::Core
  Qt6::Widgets
  egnite::egnite)

target_include_directories(
  flow_document
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/plugins>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/plugins)

egnite_add_translations(
  flow_document
  QM_DIR
  ${resources_root}/translations
  DIRS
  ${include_root}
  ${source_root}
  TS_FILES
  ${resources_root}/translations/flow_document_pl.ts
  ${resources_root}/translations/flow_document_en.ts)
# ----------------------------------------------------------------------- #
# ------------------------------- Add extensions ------------------------ #
# ----------------------------------------------------------------------- #
add_subdirectory(extensions)
# ----------------------------------------------------------------------- #
