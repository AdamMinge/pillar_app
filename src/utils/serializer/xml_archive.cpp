/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/xml_archive.h"
/* -------------------------------------------------------------------------- */

namespace utils {

/* -------------------------------- OXmlArchive ----------------------------- */

OXmlArchive::OXmlArchive(QIODevice& device) : m_writer(&device) {
  m_writer.setAutoFormatting(true);
  m_writer.writeStartDocument("1.0");
}

OXmlArchive::~OXmlArchive() { m_writer.writeEndDocument(); }

void OXmlArchive::saveStart(const QString& name) {
  m_writer.writeStartElement(name);
}

void OXmlArchive::saveEnd(const QString& name) { m_writer.writeEndElement(); }

void OXmlArchive::arrayStart(qsizetype i) {
  m_writer.writeStartElement(QLatin1String("item"));
}

void OXmlArchive::arrayEnd(qsizetype i) { m_writer.writeEndElement(); }

void OXmlArchive::save(const QVariant& value) {
  m_writer.writeCharacters(value.toString());
}

/* -------------------------------- IXmlArchive ----------------------------- */

IXmlArchive::IXmlArchive(QIODevice& device) : m_reader(&device) {}

IXmlArchive::~IXmlArchive() = default;

void IXmlArchive::loadStart(const QString& name) {}

void IXmlArchive::loadEnd(const QString& name) {}

void IXmlArchive::arrayStart(qsizetype i) {}

void IXmlArchive::arrayEnd(qsizetype i) {}

QVariant IXmlArchive::load() { return QVariant{}; }

QStringList IXmlArchive::getChildNames() const { return QStringList{}; }

qsizetype IXmlArchive::getChildCount() const { return 0; }

}  // namespace utils