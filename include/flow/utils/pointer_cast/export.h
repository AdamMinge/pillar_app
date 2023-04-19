#ifndef FLOW_QTDIALOG_EXPORT_H
#define FLOW_QTDIALOG_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(POINTER_CASST_EXPORTS)
#define POINTER_CAST_API Q_DECL_EXPORT
#else
#define POINTER_CAST_API Q_DECL_IMPORT
#endif

#endif  // FLOW_DIALOG_EXPORT_H
