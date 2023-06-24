#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(SHAPE_EXPORTS)
#define SHAPE_API Q_DECL_EXPORT
#else
#define SHAPE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
