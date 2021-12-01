#ifndef FLOW_EXPORT_H
#define FLOW_EXPORT_H


#if defined(FLOW_ENGINE_EXPORTS)
  #define FLOW_API FLOW_API_EXPORT
#else
  #define FLOW_API FLOW_API_IMPORT
#endif


#endif //FLOW_EXPORT_H
