#ifndef FLOW_FILE_SYSTEM_WATCHER_EXPORT_H
#define FLOW_FILE_SYSTEM_WATCHER_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(FILE_SYSTEM_WATCHER_EXPORTS)
#define FILE_SYSTEM_WATCHER_API FLOW_API_EXPORT
#else
#define FILE_SYSTEM_WATCHER_API FLOW_API_IMPORT
#endif


#endif//FLOW_FILE_SYSTEM_WATCHER_EXPORT_H
