#ifndef FLOW_FILE_SYSTEM_WATCHER_EXPORT_H
#define FLOW_FILE_SYSTEM_WATCHER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(FILE_SYSTEM_WATCHER_EXPORTS)
#define FILE_SYSTEM_WATCHER_API Q_DECL_EXPORT
#else
#define FILE_SYSTEM_WATCHER_API Q_DECL_IMPORT
#endif

#endif  // FLOW_FILE_SYSTEM_WATCHER_EXPORT_H
