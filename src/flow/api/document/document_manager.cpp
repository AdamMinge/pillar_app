/* ----------------------------------- Local -------------------------------- */
#include "flow/api/document/document_manager.h"
/* -------------------------------------------------------------------------- */

namespace api::document
{

  IDocumentManager::IDocumentManager(QObject *parent) : QObject(parent) {}

  IDocumentManager::~IDocumentManager() = default;

}// namespace api::document
