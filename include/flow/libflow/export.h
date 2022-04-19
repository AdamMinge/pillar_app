#ifndef FLOW_LIB_FLOW_EXPORT_H
#define FLOW_LIB_FLOW_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(LIB_FLOW_EXPORTS)
#define LIB_FLOW_API FLOW_API_EXPORT
#else
#define LIB_FLOW_API FLOW_API_IMPORT
#endif


#endif//FLOW_LIB_FLOW_EXPORT_H
