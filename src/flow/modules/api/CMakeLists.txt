# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/modules/api)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/modules/api)

set(sources
        ${source_root}/file_format.cpp

        ${source_root}/project/project.cpp
        ${source_root}/project/project_format.cpp

        ${source_root}/document/document.cpp
        ${source_root}/document/document_editor.cpp
        ${source_root}/document/new_document_widget.cpp
        ${source_root}/document/document_manager.cpp
        ${source_root}/document/document_format.cpp)

set(includes
        ${include_root}/export.h
        ${include_root}/file_format.h

        ${include_root}/project/project.h
        ${include_root}/project/project_format.h

        ${include_root}/document/document.h
        ${include_root}/document/document_editor.h
        ${include_root}/document/new_document_widget.h
        ${include_root}/document/document_manager.h
        ${include_root}/document/document_format.h)
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
flow_add_module(api
        SOURCES ${sources} ${includes}
        DEPENDS_PRIVATE Qt6::Widgets)
# -------------------------------------------------------------------------------------------------- #
