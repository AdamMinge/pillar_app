#ifndef FLOW_LINE_EDIT_EXPORT_H
#define FLOW_LINE_EDIT_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(LINE_EDIT_EXPORTS)
#define LINE_EDIT_API FLOW_API_EXPORT
#else
#define LINE_EDIT_API FLOW_API_IMPORT
#endif


#endif//FLOW_LINE_EDIT_EXPORT_H
