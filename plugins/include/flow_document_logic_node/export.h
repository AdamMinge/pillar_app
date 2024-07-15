#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LOGIC_NODE_EXPORTS)
#define LOGIC_NODE_API Q_DECL_EXPORT
#else
#define LOGIC_NODE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
