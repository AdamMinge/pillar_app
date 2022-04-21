#ifndef PLUGIN_LOGIC_NODE_API_EXPORT_H
#define PLUGIN_LOGIC_NODE_API_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(LOGIC_NODE_EXPORTS)
#define LOGIC_NODE_API FLOW_API_EXPORT
#else
#define LOGIC_NODE_API FLOW_API_IMPORT
#endif


#endif//PLUGIN_LOGIC_NODE_API_EXPORT_H
