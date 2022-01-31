/* ----------------------------------- Local -------------------------------- */
#include "flow/api/document_format.h"
/* -------------------------------------------------------------------------- */

namespace api
{

  IDocumentFormat::IDocumentFormat(QObject *parent) : IFileFormat(parent) {}

  IDocumentFormat::~IDocumentFormat() = default;

}//namespace api
