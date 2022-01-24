#ifndef FLOW_QTFILESYSTEMWATCHER_EXPORT_H
#define FLOW_QTFILESYSTEMWATCHER_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(QTFILESYSTEMWATCHER_EXPORTS)
#define QTFILESYSTEMWATCHER_API FLOW_API_EXPORT
#else
#define QTFILESYSTEMWATCHER_API FLOW_API_IMPORT
#endif


#endif//FLOW_EXPORT_H
