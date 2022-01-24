#ifndef FLOW_QTPROPERTYBROWSER_EXPORT_H
#define FLOW_QTPROPERTYBROWSER_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(QTPROPERTYBROWSER_EXPORTS)
#define QTPROPERTYBROWSER_API FLOW_API_EXPORT
#else
#define QTPROPERTYBROWSER_API FLOW_API_IMPORT
#endif


#endif//FLOW_QTPROPERTYBROWSER_EXPORT_H
