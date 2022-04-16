# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/modules/node)
set(include_root ${FLOW_SOURCE_DIR}/include/flow//modules/node)

set(sources
        ${source_root}/pin.cpp
        ${source_root}/node.cpp
        ${source_root}/connection.cpp
        ${source_root}/node_factory.cpp
        ${source_root}/node_factory_container.cpp

        ${source_root}/data/boolean_node_data.cpp
        ${source_root}/data/integer_node_data.cpp
        ${source_root}/data/character_node_data.cpp
        ${source_root}/data/floating_point_node_data.cpp
        ${source_root}/data/string_node_data.cpp)

set(includes
        ${include_root}/export.h

        ${include_root}/pin.h
        ${include_root}/node.h
        ${include_root}/connection.h
        ${include_root}/node_factory.h
        ${include_root}/node_factory_container.h

        ${include_root}/converter/type_converter.h

        ${include_root}/data/node_data.h
        ${include_root}/data/boolean_node_data.h
        ${include_root}/data/integer_node_data.h
        ${include_root}/data/character_node_data.h
        ${include_root}/data/floating_point_node_data.h
        ${include_root}/data/string_node_data.h)
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
flow_add_module(node
        SOURCES ${sources} ${includes}
        DEPENDS_PRIVATE Qt6::Widgets)
# -------------------------------------------------------------------------------------------------- #
