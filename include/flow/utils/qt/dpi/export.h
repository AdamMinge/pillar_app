#ifndef FLOW_DPI_EXPORT_H
#define FLOW_DPI_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(DPI_EXPORTS)
#define DPI_API FLOW_API_EXPORT
#else
#define DPI_API FLOW_API_IMPORT
#endif


#endif//FLOW_DPI_EXPORT_H
