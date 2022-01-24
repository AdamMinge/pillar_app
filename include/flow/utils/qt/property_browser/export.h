#ifndef FLOW_PROPERTY_BROWSER_EXPORT_H
#define FLOW_PROPERTY_BROWSER_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(PROPERTY_BROWSER_EXPORTS)
#define PROPERTY_BROWSER_API FLOW_API_EXPORT
#else
#define PROPERTY_BROWSER_API FLOW_API_IMPORT
#endif


#endif//FLOW_PROPERTY_BROWSER_EXPORT_H
