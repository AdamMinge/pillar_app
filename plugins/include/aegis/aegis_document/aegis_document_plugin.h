#ifndef AEGIS_DOCUMENT_PLUGIN_H
#define AEGIS_DOCUMENT_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_document/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis_document {

class AEGIS_DOCUMENT_API AegisDocumentPlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit AegisDocumentPlugin();
  ~AegisDocumentPlugin() override;

  void init() override;
};

}  // namespace aegis_document

#endif  // AEGIS_DOCUMENT_PLUGIN_H
