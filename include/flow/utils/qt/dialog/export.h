#ifndef FLOW_DIALOG_EXPORT_H
#define FLOW_DIALOG_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(DIALOG_EXPORTS)
#define DIALOG_API FLOW_API_EXPORT
#else
#define DIALOG_API FLOW_API_IMPORT
#endif


#endif//FLOW_DIALOG_EXPORT_H
