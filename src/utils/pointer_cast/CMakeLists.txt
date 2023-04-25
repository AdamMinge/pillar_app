# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${EGNITE_SOURCE_DIR}/src/utils/pointer_cast)
set(include_root ${EGNITE_SOURCE_DIR}/include/utils/pointer_cast)

set(sources)

set(includes ${include_root}/export.h ${include_root}/unique_ptr_cast.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries ---------------------#
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Core)
# ----------------------------------------------------------------------- #
# -------------------------- Create utils shared lib -------------------- #
# ----------------------------------------------------------------------- #
egnite_add_utils(pointer_cast SOURCES ${sources} ${includes} DEPENDS_PRIVATE
                 Qt6::Core)

target_include_directories(
  pointer_cast
  PUBLIC $<BUILD_INTERFACE:${EGNITE_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${EGNITE_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
