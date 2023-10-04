#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(MATH_NODE_EXPORTS)
#define MATH_NODE_API Q_DECL_EXPORT
#else
#define MATH_NODE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
