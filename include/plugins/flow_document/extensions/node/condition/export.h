#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(CONDITION_NODE_EXPORTS)
#define CONDITION_NODE_API Q_DECL_EXPORT
#else
#define CONDITION_NODE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
