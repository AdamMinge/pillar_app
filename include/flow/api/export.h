#ifndef FLOW_API_EXPORT_H
#define FLOW_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(API_EXPORTS)
#define API_API FLOW_API_EXPORT
#else
#define API_API FLOW_API_IMPORT
#endif


#endif//FLOW_API_EXPORT_H
