#ifndef PLUGIN_FLOW_DOCUMENT_API_EXPORT_H
#define PLUGIN_FLOW_DOCUMENT_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(FLOW_DOCUMENT_EXPORTS)
#define FLOW_DOCUMENT_API FLOW_API_EXPORT
#else
#define FLOW_DOCUMENT_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_FLOW_DOCUMENT_API_EXPORT_H
