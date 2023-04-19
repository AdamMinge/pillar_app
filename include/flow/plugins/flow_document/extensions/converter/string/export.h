#ifndef PLUGIN_STRING_CONVERTER_API_EXPORT_H
#define PLUGIN_STRING_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(STRING_CONVERTER_EXPORTS)
#define STRING_CONVERTER_API FLOW_API_EXPORT
#else
#define STRING_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_STRING_CONVERTER_API_EXPORT_H
