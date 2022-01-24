#ifndef FLOW_QTZIP_EXPORT_H
#define FLOW_QTZIP_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(QTZIP_EXPORTS)
#define QTZIP_API FLOW_API_EXPORT
#else
#define QTZIP_API FLOW_API_IMPORT
#endif


#endif//FLOW_QTZIP_EXPORT_H
