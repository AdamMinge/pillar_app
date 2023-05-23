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
    ${source_root}/flow_document_action_handler.cpp
    ${source_root}/flow_document_plugin.cpp
    ${source_root}/flow_document_reader.cpp
    ${source_root}/flow_document_writer.cpp
    ${source_root}/flow_editor.cpp
    ${source_root}/flow_script_module.cpp
    ${source_root}/new_flow_document_widget.cpp
    ${source_root}/event/change_event.cpp
    ${source_root}/event/layer_change_event.cpp
    ${source_root}/flow/node.cpp
    ${source_root}/flow/object.cpp
    ${source_root}/flow/pin.cpp
    ${source_root}/flow/factory.cpp
    ${source_root}/flow/group_factory.cpp
    ${source_root}/flow/node_factory.cpp
    ${source_root}/flow/flow.cpp
    ${source_root}/flow/layer.cpp
    ${source_root}/flow/group_layer.cpp
    ${source_root}/flow/node_layer.cpp
    ${source_root}/flow/layer_iterator.cpp
    ${source_root}/command/add_remove_layer.cpp
    ${source_root}/command/change_layer.cpp
    ${source_root}/command/reparent_layer.cpp
    ${source_root}/command/raise_lower_layer.cpp
    ${source_root}/command/duplicate_layer.cpp
    ${source_root}/component/factories/factories_dock.cpp
    ${source_root}/component/factories/factories_view.cpp
    ${source_root}/component/factories/factories_tree_model.cpp
    ${source_root}/component/properties/properties_dock.cpp
    ${source_root}/component/nodes/nodes_dock.cpp
    ${source_root}/component/nodes/nodes_view.cpp
    ${source_root}/component/nodes/nodes_tree_model.cpp
    ${source_root}/component/layers/layers_dock.cpp
    ${source_root}/component/layers/layers_view.cpp
    ${source_root}/component/layers/layers_tree_model.cpp
    ${source_root}/component/scene/flow_scene.cpp
    ${source_root}/component/scene/flow_view.cpp
    ${source_root}/component/scene/item/graphics_item.cpp
    ${source_root}/component/scene/item/node_graphics_item.cpp
    ${source_root}/component/scene/item/selection_rectangle.cpp
    ${source_root}/component/scene/style/style_manager.cpp
    ${source_root}/component/scene/style/style_writer.cpp
    ${source_root}/component/scene/style/style_reader.cpp
    ${source_root}/component/scene/style/style.cpp
    ${source_root}/component/scene/tool/tools_bar.cpp
    ${source_root}/component/scene/tool/abstract_tool.cpp
    ${source_root}/component/scene/tool/selection_tool.cpp)

set(includes
    ${include_root}/export.h
    ${include_root}/global.h
    ${include_root}/concept.h
    ${include_root}/resources.h
    ${include_root}/flow_document.h
    ${include_root}/flow_document_format.h
    ${include_root}/flow_document_format_flow.h
    ${include_root}/flow_document_action_handler.h
    ${include_root}/flow_document_plugin.h
    ${include_root}/flow_document_reader.h
    ${include_root}/flow_document_writer.h
    ${include_root}/flow_editor.h
    ${include_root}/flow_script_module.h
    ${include_root}/new_flow_document_widget.h
    ${include_root}/event/change_event.h
    ${include_root}/event/layer_change_event.h
    ${include_root}/flow/node.h
    ${include_root}/flow/object.h
    ${include_root}/flow/pin.h
    ${include_root}/flow/factory.h
    ${include_root}/flow/group_factory.h
    ${include_root}/flow/node_factory.h
    ${include_root}/flow/flow.h
    ${include_root}/flow/layer.h
    ${include_root}/flow/group_layer.h
    ${include_root}/flow/node_layer.h
    ${include_root}/flow/layer_iterator.h
    ${include_root}/command/add_remove_layer.h
    ${include_root}/command/change_value.h
    ${include_root}/command/change_layer.h
    ${include_root}/command/reparent_layer.h
    ${include_root}/command/raise_lower_layer.h
    ${include_root}/command/duplicate_layer.h
    ${include_root}/component/factories/factories_dock.h
    ${include_root}/component/factories/factories_view.h
    ${include_root}/component/factories/factories_tree_model.h
    ${include_root}/component/properties/properties_dock.h
    ${include_root}/component/nodes/nodes_dock.h
    ${include_root}/component/nodes/nodes_view.h
    ${include_root}/component/nodes/nodes_tree_model.h
    ${include_root}/component/layers/layers_dock.h
    ${include_root}/component/layers/layers_view.h
    ${include_root}/component/layers/layers_tree_model.h
    ${include_root}/component/scene/flow_scene.h
    ${include_root}/component/scene/flow_view.h
    ${include_root}/component/scene/item/graphics_item.h
    ${include_root}/component/scene/item/node_graphics_item.h
    ${include_root}/component/scene/item/selection_rectangle.h
    ${include_root}/component/scene/style/style_manager.h
    ${include_root}/component/scene/style/style_writer.h
    ${include_root}/component/scene/style/style_reader.h
    ${include_root}/component/scene/style/style.h
    ${include_root}/component/scene/tool/tools_bar.h
    ${include_root}/component/scene/tool/abstract_tool.h
    ${include_root}/component/scene/tool/selection_tool.h)

set(resources ${resources_root}/flow_document.qrc)

set(uis
    ${uis_root}/new_flow_document_widget.ui ${uis_root}/factories_dock.ui
    ${uis_root}/properties_dock.ui ${uis_root}/layers_dock.ui
    ${uis_root}/nodes_dock.ui)
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
  egnite::egnite
  utils::model
  utils::delegate)

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
