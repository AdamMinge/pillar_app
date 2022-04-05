#ifndef FLOW_STACKED_WIDGET_EXPORT_H
#define FLOW_STACKED_WIDGET_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(STACKED_WIDGET_EXPORTS)
#define STACKED_WIDGET_API FLOW_API_EXPORT
#else
#define STACKED_WIDGET_API FLOW_API_IMPORT
#endif


#endif//FLOW_STACKED_WIDGET_EXPORT_H
