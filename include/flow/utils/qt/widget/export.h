#ifndef FLOW_WIDGET_EXPORT_H
#define FLOW_WIDGET_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(WIDGET_EXPORTS)
#define WIDGET_API FLOW_API_EXPORT
#else
#define WIDGET_API FLOW_API_IMPORT
#endif


#endif//FLOW_WIDGET_EXPORT_H
