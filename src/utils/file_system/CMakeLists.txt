# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/utils/file_system)
set(include_root ${EGNITE_SOURCE_DIR}/include/utils/file_system)

set(sources ${source_root}/file_system_watcher.cpp
            ${source_root}/file_system_proxy_model.cpp)

set(includes ${include_root}/export.h ${include_root}/file_system_watcher.h
             ${include_root}/file_system_proxy_model.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration -------------------#
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries ---------------------#
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create utils shared lib ---------------------#
# ----------------------------------------------------------------------- #
egnite_add_utils(file_system SOURCES ${sources} ${includes} DEPENDS_PRIVATE
                 Qt6::Widgets)

target_include_directories(
  file_system
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
