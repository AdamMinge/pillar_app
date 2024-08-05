#ifndef AEGIS_SEARCH_COMMAND_EXPORT_H
#define AEGIS_SEARCH_COMMAND_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(AEGIS_SEARCH_COMMAND_EXPORTS)
#define LIB_AEGIS_SEARCH_COMMAND_API Q_DECL_EXPORT
#else
#define LIB_AEGIS_SEARCH_COMMAND_API Q_DECL_IMPORT
#endif

#endif  // AEGIS_SEARCH_COMMAND_EXPORT_H
