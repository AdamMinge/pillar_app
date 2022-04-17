#ifndef BOOLEAN_CONVERTER_API_EXPORT_H
#define BOOLEAN_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(BOOLEAN_CONVERTER_EXPORTS)
#define BOOLEAN_CONVERTER_API FLOW_API_EXPORT
#else
#define BOOLEAN_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//BOOLEAN_CONVERTER_API_EXPORT_H
