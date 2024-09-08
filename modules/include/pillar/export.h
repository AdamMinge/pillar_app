#ifndef PILLAR_EXPORT_H
#define PILLAR_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "pillar/config.h"
/* -------------------------------------------------------------------------- */

#if defined(LIB_PILLAR_EXPORTS)
#define LIB_PILLAR_API PILLAR_API_EXPORT
#else
#define LIB_PILLAR_API PILLAR_API_IMPORT
#endif

#endif  // PILLAR_EXPORT_H
