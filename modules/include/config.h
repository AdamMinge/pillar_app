/* -------------------------------------------------------------------------- */
#ifndef PILLAR_CONFIG_H
#define PILLAR_CONFIG_H
/* -------------------------------------------------------------------------- */
/* ---------------------------- Define PILLAR version ----------------------- */
/* -------------------------------------------------------------------------- */
// clang-format off

#define PILLAR_VERSION_MAJOR 0
#define PILLAR_VERSION_MINOR 1
#define PILLAR_VERSION_PATCH 0
#define PILLAR_VERSION 0.1.0
#define PILLAR_VERSION_STR "0.1.0"

// clang-format on
/* -------------------------------------------------------------------------- */
/* ----------------------- Identify the operating system -------------------- */
/* -------------------------------------------------------------------------- */
#if defined(_WIN32)
#define PILLAR_OS_WINDOWS
#elif defined(__linux__)
#define PILLAR_OS_LINUX
#else
#error This operating system is not supported by PILLAR library
#endif
/* -------------------------------------------------------------------------- */
/* ------------------------ Define a portable debug macro ------------------- */
/* -------------------------------------------------------------------------- */
#if !defined(NDEBUG)
#define PILLAR_DEBUG
#endif
/* -------------------------------------------------------------------------- */
/* -------------------- Define helpers to set items as deprecated ----------- */
/* -------------------------------------------------------------------------- */
#if !defined(PILLAR_DEPRECATED_WARNINGS)
#define PILLAR_DEPRECATED [[deprecated]]
#else
#define PILLAR_DEPRECATED
#endif
/* -------------------------------------------------------------------------- */
#endif  // PILLAR_CONFIG_H
/* -------------------------------------------------------------------------- */
