#ifndef FLOW_EXPORT_H
#define FLOW_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(TOOLS_SHARED_EXPORTS)
#define TOOLS_SHARED_API FLOW_API_EXPORT
#else
#define TOOLS_SHARED_API FLOW_API_IMPORT
#endif


#endif//FLOW_EXPORT_H
