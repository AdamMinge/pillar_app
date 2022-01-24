#ifndef FLOW_QTLINEEDIT_EXPORT_H
#define FLOW_QTLINEEDIT_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(QTLINEEDIT_EXPORTS)
#define QTLINEEDIT_API FLOW_API_EXPORT
#else
#define QTLINEEDIT_API FLOW_API_IMPORT
#endif


#endif//FLOW_QTLINEEDIT_EXPORT_H
