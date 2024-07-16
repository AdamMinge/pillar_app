#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(STRING_NODE_EXPORTS)
#define STRING_NODE_API Q_DECL_EXPORT
#else
#define STRING_NODE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
