# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${FLOW_SOURCE_DIR}/src/utils/color)
set(include_root ${FLOW_SOURCE_DIR}/include/utils/color)

set(sources ${source_root}/color.cpp)

set(includes ${include_root}/export.h ${include_root}/color.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create utils shared lib -------------------- #
# ----------------------------------------------------------------------- #
flow_add_utils(color SOURCES ${sources} ${includes} DEPENDS_PRIVATE
               Qt6::Widgets)

target_include_directories(
  color
  PUBLIC $<BUILD_INTERFACE:${FLOW_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${FLOW_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
