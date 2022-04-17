#ifndef FLOW_COLOR_EXPORT_H
#define FLOW_COLOR_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(COLOR_EXPORTS)
#define COLOR_API FLOW_API_EXPORT
#else
#define COLOR_API FLOW_API_IMPORT
#endif


#endif//FLOW_COLOR_EXPORT_H
