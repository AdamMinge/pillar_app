#ifndef FLOW_QTDIALOG_EXPORT_H
#define FLOW_QTDIALOG_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(API_EXPORTS)
#define API_API FLOW_API_EXPORT
#else
#define API_API FLOW_API_IMPORT
#endif


#endif//FLOW_EXPORT_H
