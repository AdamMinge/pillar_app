#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LIB_FLOW_LOGIC_NODE_EXPORTS)
#define LIB_FLOW_LOGIC_NODE_API Q_DECL_EXPORT
#else
#define LIB_FLOW_LOGIC_NODE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
