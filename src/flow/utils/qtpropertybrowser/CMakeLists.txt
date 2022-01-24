# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/flow/utils/qtpropertybrowser)
set(include_root ${FLOW_SOURCE_DIR}/include/flow/utils/qtpropertybrowser)

set(sources
        ${source_root}/qtbuttonpropertybrowser.cpp
        ${source_root}/qteditorfactory.cpp
        ${source_root}/qtgroupboxpropertybrowser.cpp
        ${source_root}/qtpropertybrowser.cpp
        ${source_root}/qtpropertybrowserutils.cpp
        ${source_root}/qtpropertymanager.cpp
        ${source_root}/qttreepropertybrowser.cpp
        ${source_root}/qtvariantproperty.cpp
        ${source_root}/priv/qtpropertybrowserutils_p.h)

set(includes
        ${include_root}/export.h
        ${include_root}/qtbuttonpropertybrowser.h
        ${include_root}/qteditorfactory.h
        ${include_root}/qtgroupboxpropertybrowser.h
        ${include_root}/qtpropertybrowser.h
        ${include_root}/qtpropertymanager.h
        ${include_root}/qttreepropertybrowser.h
        ${include_root}/qtvariantproperty.h)
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
flow_add_utils(qtpropertybrowser
        SOURCES ${sources} ${includes}
        DEPENDS Qt6::Widgets)
# -------------------------------------------------------------------------------------------------- #
