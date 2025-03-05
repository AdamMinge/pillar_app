#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(MIGRATE_V2_0_0_TO_V3_0_0_EXPORTS)
#define LIB_PLUGIN_API Q_DECL_EXPORT
#else
#define LIB_PLUGIN_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
