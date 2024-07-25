#ifndef FLOW_CONDITION_NODE_EXPORT_H
#define FLOW_CONDITION_NODE_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(FLOW_CONDITION_NODE_EXPORTS)
#define LIB_FLOW_CONDITION_NODE_API Q_DECL_EXPORT
#else
#define LIB_FLOW_CONDITION_NODE_API Q_DECL_IMPORT
#endif

#endif  // FLOW_CONDITION_NODE_EXPORT_H
