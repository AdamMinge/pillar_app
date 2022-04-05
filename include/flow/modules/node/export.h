#ifndef FLOW_NODE_EXPORT_H
#define FLOW_NODE_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(NODE_EXPORTS)
#define NODE_API FLOW_API_EXPORT
#else
#define NODE_API FLOW_API_IMPORT
#endif


#endif//FLOW_NODE_EXPORT_H
