/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/xml_archive.h"
/* -------------------------------------------------------------------------- */

namespace utils {

/* -------------------------------- OXmlArchive ----------------------------- */

OXmlArchive::OXmlArchive(QIODevice& device) : m_writer(&device) {}

OXmlArchive::~OXmlArchive() = default;

void OXmlArchive::startSave(const QString& name) {}

void OXmlArchive::endSave(const QString& name) {}

void OXmlArchive::save(const QVariant& value) {}

/* -------------------------------- IXmlArchive ----------------------------- */

IXmlArchive::IXmlArchive(QIODevice& device) : m_reader(&device) {}

IXmlArchive::~IXmlArchive() = default;

void IXmlArchive::startLoad(const QString& name) {}

void IXmlArchive::endLoad(const QString& name) {}

QVariant IXmlArchive::load() { return QVariant{}; }

}  // namespace utils