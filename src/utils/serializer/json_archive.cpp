/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/json_archive.h"
/* -------------------------------------------------------------------------- */

namespace utils {

/* ------------------------------- OJsonArchive ----------------------------- */

OJsonArchive::OJsonArchive(QIODevice& device) : m_device(device) {}

OJsonArchive::~OJsonArchive() = default;

void OJsonArchive::startSave(const QString& name) {}

void OJsonArchive::endSave(const QString& name) {}

void OJsonArchive::save(const QVariant& value) {}

/* ------------------------------- IJsonArchive ----------------------------- */

IJsonArchive::IJsonArchive(QIODevice& device) : m_device(device) {}

IJsonArchive::~IJsonArchive() = default;

void IJsonArchive::startLoad(const QString& name) {}

void IJsonArchive::endLoad(const QString& name) {}

QVariant IJsonArchive::load() { return QVariant{}; }

}  // namespace utils