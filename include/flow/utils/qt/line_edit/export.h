#ifndef FLOW_LINE_EDIT_EXPORT_H
#define FLOW_LINE_EDIT_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LINE_EDIT_EXPORTS)
#define LINE_EDIT_API Q_DECL_EXPORT
#else
#define LINE_EDIT_API Q_DECL_IMPORT
#endif

#endif  // FLOW_LINE_EDIT_EXPORT_H
