#ifndef PLUGIN_FLOATING_POINT_CONVERTER_API_EXPORT_H
#define PLUGIN_FLOATING_POINT_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(FLOATING_POINT_CONVERTER_EXPORTS)
#define FLOATING_POINT_CONVERTER_API FLOW_API_EXPORT
#else
#define FLOATING_POINT_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_FLOATING_POINT_CONVERTER_API_EXPORT_H
