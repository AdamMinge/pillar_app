#ifndef FLOW_QTVIEW_EXPORT_H
#define FLOW_QTVIEW_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(QTVIEW_EXPORTS)
#define QTVIEW_API FLOW_API_EXPORT
#else
#define QTVIEW_API FLOW_API_IMPORT
#endif


#endif//FLOW_QTVIEW_EXPORT_H
