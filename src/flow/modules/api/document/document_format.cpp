/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/api/document/document_format.h"
/* -------------------------------------------------------------------------- */

namespace api::document
{

  IDocumentFormat::IDocumentFormat(QObject *parent) : IFileFormat(parent) {}

  IDocumentFormat::~IDocumentFormat() = default;

}//namespace api::document
