#ifndef PILLAR_EXPORT_H
#define PILLAR_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LIB_PILLAR_EXPORTS)
#define LIB_PILLAR_API Q_DECL_EXPORT
#else
#define LIB_PILLAR_API Q_DECL_IMPORT
#endif

#endif  // PILLAR_EXPORT_H
