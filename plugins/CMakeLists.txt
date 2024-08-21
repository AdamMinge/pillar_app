# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
add_subdirectory(src/flow/document)
add_subdirectory(src/flow/condition_node)
add_subdirectory(src/flow/logic_node)
add_subdirectory(src/flow/math_node)
add_subdirectory(src/flow/string_node)

add_subdirectory(src/aegis/server)
# ----------------------------------------------------------------------- #
