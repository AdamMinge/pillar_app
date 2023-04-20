#ifndef PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_EXPORT_H
#define PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LOGIC_NODE_EXPORTS)
#define LOGIC_NODE_API Q_DECL_EXPORT
#else
#define LOGIC_NODE_API Q_DECL_IMPORT
#endif

#endif  // PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_EXPORT_H
