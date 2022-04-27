#ifndef PLUGIN_INTEGER_CONVERTER_API_EXPORT_H
#define PLUGIN_INTEGER_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(INTEGER_CONVERTER_EXPORTS)
#define INTEGER_CONVERTER_API FLOW_API_EXPORT
#else
#define INTEGER_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_INTEGER_CONVERTER_API_EXPORT_H
