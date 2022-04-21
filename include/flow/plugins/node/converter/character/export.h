#ifndef PLUGIN_CHARACTER_CONVERTER_API_EXPORT_H
#define PLUGIN_CHARACTER_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(CHARACTER_CONVERTER_EXPORTS)
#define CHARACTER_CONVERTER_API FLOW_API_EXPORT
#else
#define CHARACTER_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_CHARACTER_CONVERTER_API_EXPORT_H
