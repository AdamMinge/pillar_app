#ifndef FLOW_QTDPI_EXPORT_H
#define FLOW_QTDPI_EXPORT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

#if defined(QTDPI_EXPORTS)
#define QTDPI_API FLOW_API_EXPORT
#else
#define QTDPI_API FLOW_API_IMPORT
#endif


#endif//FLOW_QTDPI_EXPORT_H
