#ifndef FLOW_ACTION_EXPORT_H
#define FLOW_ACTION_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(ACTION_EXPORTS)
#define ACTION_API FLOW_API_EXPORT
#else
#define ACTION_API FLOW_API_IMPORT
#endif


#endif//FLOW_ACTION_EXPORT_H
