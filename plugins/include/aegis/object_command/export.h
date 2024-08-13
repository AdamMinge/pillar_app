#ifndef AEGIS_OBJECT_COMMAND_EXPORT_H
#define AEGIS_OBJECT_COMMAND_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(AEGIS_OBJECT_COMMAND_EXPORTS)
#define LIB_AEGIS_OBJECT_COMMAND_API Q_DECL_EXPORT
#else
#define LIB_AEGIS_OBJECT_COMMAND_API Q_DECL_IMPORT
#endif

#endif  // AEGIS_OBJECT_COMMAND_EXPORT_H
