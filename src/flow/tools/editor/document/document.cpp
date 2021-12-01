/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/document.h"
#include "flow/tools/editor/document/document_serializer.h"
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_undo_stack(new QUndoStack(this))
{
  connect(m_undo_stack, &QUndoStack::cleanChanged, this, &Document::modifiedChanged);
}

Document::~Document() = default;

Document::Type Document::getType() const
{
  return m_type;
}

void Document::setFileName(const QString& file_name)
{
  if(m_file_name == file_name)
    return;

  auto old_file_name = m_file_name;
  m_file_name = file_name;

  Q_EMIT fileNameChanged(file_name, old_file_name);
}

QString Document::getFileName() const
{
  return m_file_name;
}

QString Document::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled.%1").arg(getDocumentExtension());

  return displayName;
}

QDateTime Document::getLastModified() const
{
  return QFileInfo(m_file_name).lastModified();
}

bool Document::isModified() const
{
  return !m_undo_stack->isClean();
}

QUndoStack* Document::getUndoStack() const
{
  return m_undo_stack;
}

bool Document::save(const QString& file_name)
{
  auto serializer = DocumentSerializer();
  auto bytearray = serializer.serialize(*this);

  auto file = QFile(file_name);
  if(!file.open(QIODevice::WriteOnly))
    return false;

  file.write(bytearray);
  file.close();

  getUndoStack()->setClean();
  setFileName(file_name);

  Q_EMIT saved();
  return true;
}

std::unique_ptr<Document> Document::load(const QString& file_name)
{
  auto file = QFile(file_name);
  if(!file.open(QIODevice::ReadOnly))
    return nullptr;

  auto array = file.readAll();
  auto serializer = DocumentSerializer();

  auto document = serializer.deserialize(array);
  if(document)
    document->setFileName(file_name);

  return document;
}

QString Document::getDocumentFileFilter() const
{
  return getDocumentFileFilter(m_type);
}

QString Document::getDocumentFileFilter(Type type)
{
  return QString("%1 (*.%2)").arg(
      getDocumentDisplayType(type),
      getDocumentExtension(type));
}

QStringList Document::getDocumentFileFilters()
{
  auto filters = QStringList();
  for(auto type_id = static_cast<int>(Type::Flow); type_id < static_cast<int>(Type::Unknown); ++type_id)
    filters << getDocumentFileFilter(static_cast<Type>(type_id));

  return filters;
}

QString Document::getDocumentExtension() const
{
  return getDocumentExtension(m_type);
}

QString Document::getDocumentExtension(Type type)
{
  constexpr const char* type_to_extension[] = {
      "flow",
      ""
  };

  return type_to_extension[static_cast<int>(type)];
}

QStringList Document::getDocumentExtensions()
{
  auto extensions = QStringList();
  for(auto type_id = static_cast<int>(Type::Flow); type_id < static_cast<int>(Type::Unknown); ++type_id)
    extensions << getDocumentExtension(static_cast<Type>(type_id));

  return extensions;
}

QIcon Document::getDocumentIcon() const
{
  return getDocumentIcon(m_type);
}

QIcon Document::getDocumentIcon(Type type)
{
  constexpr const char* type_to_icon[] = {
      ":/images/64x64/flow_document.png",
      ":/images/64x64/unknown_documents.png"
  };

  return QIcon(type_to_icon[static_cast<int>(type)]);
}

QString Document::getDocumentDisplayType(Type type)
{
  constexpr const char* type_to_display_name[] = {
      "Flow Document",
      "Unknown Document"
  };

  return type_to_display_name[static_cast<int>(type)];
}