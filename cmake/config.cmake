# ----------------------------------------------------------------------- #
# ----------- Define a macro that helps defining an option -------------- #
# ----------------------------------------------------------------------- #
macro(flow_set_option var default type docstring)
  if(NOT DEFINED ${var})
    set(${var} ${default})
  endif()
  set(${var}
      ${${var}}
      CACHE ${type} ${docstring} FORCE)
endmacro()
# ----------------------------------------------------------------------- #
# ---------------------------- Detect the OS ---------------------------- #
# ----------------------------------------------------------------------- #
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(FLOW_OS_WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(FLOW_OS_LINUX TRUE)
else()
  message(FATAL_ERROR "Unsupported operating system or environment")
endif()
# ----------------------------------------------------------------------- #
# ---------------------------- Define options --------------------------- #
# ----------------------------------------------------------------------- #
flow_set_option(
  BUILD_SHARED_LIBS
  TRUE
  BOOL
  "TRUE to build FLOW dependencies as shared libraries, FALSE to build it as static libraries"
)
flow_set_option(
  FLOW_DEPRECATED_WARNINGS TRUE BOOL
  "FALSE to disable deprecated warning, TRUE to enable depracated warning")
flow_set_option(FLOW_BUILD_DEPS FALSE BOOL
                "TRUE to build dependecies , FALSE to ignore them")
flow_set_option(FLOW_BUILD_TEST TRUE BOOL
                "TRUE to build the flow-tests, FALSE to ignore them")
flow_set_option(FLOW_BUILD_DOCUMENTATION TRUE BOOL
                "TRUE to build the documentation, FALSE to ignore them")
flow_set_option(FLOW_ENABLE_CLANG_TIDY TRUE BOOL
                "TRUE to enable clang tidy, FALSE to ignore them")
flow_set_option(FLOW_ENABLE_CPPCHECK TRUE BOOL
                "TRUE to enable cppcheck, FALSE to ignore them")
# ----------------------------------------------------------------------- #
# -------------------------- Set other options -------------------------- #
# ----------------------------------------------------------------------- #
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${FLOW_SOURCE_DIR}/cmake/modules)
# ----------------------------------------------------------------------- #
