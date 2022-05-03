# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/plugins/node/node/logic)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/plugins/node/node/logic)
set(resources_root ${FLOW_SOURCE_DIR}/resources)

set(sources
        ${source_root}/logic_node.cpp
        ${source_root}/logic_node_not.cpp
        ${source_root}/logic_node_and.cpp
        ${source_root}/logic_node_or.cpp
        ${source_root}/node_factory.cpp)

set(includes
        ${include_root}/export.h
        ${include_root}/logic_node.h
        ${include_root}/logic_node_not.h
        ${include_root}/logic_node_and.h
        ${include_root}/logic_node_or.h
        ${include_root}/node_factory.h)

set(resources)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Qt libraries configuration ------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# -------------------------------------------------------------------------------------------------- #
# ------------------------------------ Create utils shared lib ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
flow_add_plugins(logic_node
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS_PRIVATE Qt6::Widgets flow::lib_flow)
# -------------------------------------------------------------------------------------------------- #
