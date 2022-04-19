# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/plugins/node/converter/character)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/plugins/node/converter/character)
set(resources_root ${FLOW_SOURCE_DIR}/resources)

set(sources
        ${source_root}/character_to_boolean_converter.cpp
        ${source_root}/character_to_integer_converter.cpp
        ${source_root}/character_to_string_converter.cpp
        ${source_root}/converter_plugin.cpp)

set(includes
        ${include_root}/export.h
        ${include_root}/character_to_boolean_converter.h
        ${include_root}/character_to_integer_converter.h
        ${include_root}/character_to_string_converter.h
        ${include_root}/converter_plugin.h)
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
flow_add_plugins(character_converter
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS_PRIVATE Qt6::Widgets flow::lib_flow)
# -------------------------------------------------------------------------------------------------- #
