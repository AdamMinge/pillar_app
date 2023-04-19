#ifndef PLUGIN_BOOLEAN_CONVERTER_API_EXPORT_H
#define PLUGIN_BOOLEAN_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(BOOLEAN_CONVERTER_EXPORTS)
#define BOOLEAN_CONVERTER_API FLOW_API_EXPORT
#else
#define BOOLEAN_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_BOOLEAN_CONVERTER_API_EXPORT_H
