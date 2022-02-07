/* ----------------------------------- Local -------------------------------- */
#include "flow/api/document/document_editor.h"
/* -------------------------------------------------------------------------- */

namespace api::document
{
  IDocumentEditor::IDocumentEditor(QObject *parent) : QObject(parent) {}

  IDocumentEditor::~IDocumentEditor() = default;
}// namespace api::document
