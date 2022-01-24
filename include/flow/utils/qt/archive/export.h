#ifndef FLOW_ARCHIVE_EXPORT_H
#define FLOW_ARCHIVE_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(ARCHIVE_EXPORTS)
#define ARCHIVE_API FLOW_API_EXPORT
#else
#define ARCHIVE_API FLOW_API_IMPORT
#endif

#endif//FLOW_ARCHIVE_EXPORT_H
