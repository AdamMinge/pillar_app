/* -------------------------------------------------------------------------------------------------- */
#ifndef FLOW_CONFIG_H
#define FLOW_CONFIG_H
/* -------------------------------------------------------------------------------------------------- */
/* ------------------------------------- Define FLOW version --------------------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#define FLOW_VERSION_MAJOR 0
#define FLOW_VERSION_MINOR 1
#define FLOW_VERSION_PATCH 0
#define FLOW_VERSION 0.1.0
#define FLOW_VERSION_STR "0.1.0"
/* -------------------------------------------------------------------------------------------------- */
/* --------------------------------- Identify the operating system ---------------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if defined(_WIN32)
    #define FLOW_OS_WINDOWS
#elif defined(__linux__)
    #define FLOW_OS_LINUX
#else
    #error This operating system is not supported by FLOW library
#endif
/* -------------------------------------------------------------------------------------------------- */
/* --------------------------------- Define a portable debug macro ---------------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if !defined(NDEBUG)
    #define FLOW_DEBUG
#endif
/* -------------------------------------------------------------------------------------------------- */
/* ------------------- Define helpers to create portable import / export macros --------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if !defined(FLOW_STATIC)
    #if defined(FLOW_OS_WINDOWS)
        #define FLOW_API_EXPORT __declspec(dllexport)
        #define FLOW_API_IMPORT __declspec(dllimport)
    #else
        #if __GNUC__ >= 4
            #define FLOW_API_EXPORT __attribute__ ((__visibility__ ("default")))
            #define FLOW_API_IMPORT __attribute__ ((__visibility__ ("default")))
        #else
            #define FLOW_API_EXPORT
            #define FLOW_API_IMPORT
        #endif
    #endif
#else
    #define FLOW_API_EXPORT
    #define FLOW_API_IMPORT
#endif
/* -------------------------------------------------------------------------------------------------- */
/* --------------------------- Define helpers to set items as depracted ----------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if !defined(FLOW_DEPRECATED_WARNINGS)
    #define FLOW_DEPRECATED [[deprecated]]
#else
    #define FLOW_DEPRECATED
#endif
/* -------------------------------------------------------------------------------------------------- */
#endif //FLOW_CONFIG_H
/* -------------------------------------------------------------------------------------------------- */
