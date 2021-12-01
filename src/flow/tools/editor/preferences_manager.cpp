/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/preferences_manager.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<PreferencesManager> PreferencesManager::m_instance = QScopedPointer<PreferencesManager>(nullptr);

PreferencesManager& PreferencesManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new PreferencesManager);

  return *m_instance;
}

void PreferencesManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

PreferencesManager::PreferencesManager()
{
  load();
}

PreferencesManager::~PreferencesManager()
{
  save();
}

void PreferencesManager::load()
{
  m_recent_document_files = m_settings.value(
      "document/recent_document_files", QStringList{}).toStringList();
}

void PreferencesManager::save()
{
  m_settings.setValue(
      "document/recent_document_files", m_recent_document_files);
}

void PreferencesManager::addRecentDocumentFile(const QString& recent_file)
{
  if(!m_recent_document_files.contains(recent_file))
    m_recent_document_files << recent_file;

  Q_EMIT recentDocumentFilesChanged();
}

void PreferencesManager::clearRecentDocumentFiles()
{
  m_recent_document_files.clear();
  Q_EMIT recentDocumentFilesChanged();
}

QStringList PreferencesManager::getRecentDocumentFiles() const
{
  return m_recent_document_files;
}

bool PreferencesManager::contains(const QString& key)
{
  return m_settings.contains(key);
}

void PreferencesManager::remove(const QString& key)
{
  m_settings.remove(key);
}

void PreferencesManager::clear()
{
  m_settings.clear();
}

QStringList PreferencesManager::getAllKeys() const
{
  return m_settings.allKeys();
}