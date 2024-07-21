# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
add_subdirectory(src/flow/flow_document)
add_subdirectory(src/flow/flow_document_condition_node)
add_subdirectory(src/flow/flow_document_logic_node)
add_subdirectory(src/flow/flow_document_math_node)
add_subdirectory(src/flow/flow_document_string_node)

add_subdirectory(src/aegis/aegis_server)
# ----------------------------------------------------------------------- #
