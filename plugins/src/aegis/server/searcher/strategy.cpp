/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/searcher/strategy.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMetaProperty>
#include <QVariantMap>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- SearchingStrategy -------------------------- */

SearchingStrategy::SearchingStrategy() = default;

SearchingStrategy::~SearchingStrategy() = default;

/* ------------------------------- TypeSearching ---------------------------- */

TypeSearching::TypeSearching() = default;

TypeSearching::~TypeSearching() = default;

bool TypeSearching::matchesQuery(QObject* object,
                                 const QVariantMap& query) const {
  if (query.contains(TypeQuery)) {
    return object->metaObject()->className() == query[TypeQuery];
  }

  return true;
}

QVariantMap TypeSearching::createQuery(QObject* object) const {
  auto query = QVariantMap{};
  query[TypeQuery] = object->metaObject()->className();

  return query;
}

/* ---------------------------- PropertiesSearching ------------------------- */

PropertiesSearching::PropertiesSearching() = default;

PropertiesSearching::~PropertiesSearching() = default;

bool PropertiesSearching::matchesQuery(QObject* object,
                                       const QVariantMap& query) const {
  if (query.contains(PropertiesQuery)) {
    const auto properties = query[PropertiesQuery].toMap();
    for (auto property_name : properties.keys()) {
      if (properties[property_name] !=
          object->property(property_name.toUtf8().constData()))
        return false;
    }
  }

  return true;
}

QVariantMap PropertiesSearching::createQuery(QObject* object) const {
  auto query = QVariantMap{};

  auto properties = QVariantMap{};
  const auto meta_object = object->metaObject();
  for (auto i = 0; i < meta_object->propertyCount(); ++i) {
    const auto property = meta_object->property(i);
    properties[property.name()] = object->property(property.name());
  }

  query[PropertiesQuery] = properties;

  return query;
}

/* ------------------------------- PathSearching ---------------------------- */

PathSearching::PathSearching() = default;

PathSearching::~PathSearching() = default;

bool PathSearching::matchesQuery(QObject* object,
                                 const QVariantMap& query) const {
  if (query.contains(pathQuery)) {
    return getPath(object) == query[pathQuery];
  }

  return true;
}

QVariantMap PathSearching::createQuery(QObject* object) const {
  auto query = QVariantMap{};
  query[pathQuery] = getPath(object);

  return query;
}

QString PathSearching::getPath(QObject* object) const {
  auto objects_path = QStringList{};

  while (object) {
    auto object_name = object->objectName();
    if (object_name.isEmpty()) {
      object_name = object->metaObject()->className();
    }

    objects_path.prepend(object_name);
    object = object->parent();
  }

  return objects_path.join(".");
}

}  // namespace aegis
