#ifndef STRING_CONVERTER_API_EXPORT_H
#define STRING_CONVERTER_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(STRING_CONVERTER_EXPORTS)
#define STRING_CONVERTER_API FLOW_API_EXPORT
#else
#define STRING_CONVERTER_API FLOW_API_IMPORT
#endif


#endif//STRING_CONVERTER_API_EXPORT_H
