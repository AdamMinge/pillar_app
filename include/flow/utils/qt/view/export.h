#ifndef FLOW_VIEW_EXPORT_H
#define FLOW_VIEW_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(VIEW_EXPORTS)
#define VIEW_API FLOW_API_EXPORT
#else
#define VIEW_API FLOW_API_IMPORT
#endif


#endif//FLOW_VIEW_EXPORT_H
