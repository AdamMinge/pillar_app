/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/search/strategy.h"
/* --------------------------------- Standard ------------------------------- */
#include <set>
/* ------------------------------------ Qt ---------------------------------- */
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMetaProperty>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSlider>
#include <QTabWidget>
#include <QTableWidget>
#include <QVariantMap>
#include <QWidget>
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
  if (query.contains(type_query)) {
    return object->metaObject()->className() == query[type_query];
  }

  return true;
}

QVariantMap TypeSearching::createQuery(QObject* object) const {
  auto query = QVariantMap{};
  query[type_query] = object->metaObject()->className();

  return query;
}

/* ---------------------------- PropertiesSearching ------------------------- */

PropertiesSearching::PropertiesSearching() = default;

PropertiesSearching::~PropertiesSearching() = default;

bool PropertiesSearching::matchesQuery(QObject* object,
                                       const QVariantMap& query) const {
  if (query.contains(properties_query)) {
    const auto properties = query[properties_query].toMap();

    const auto used_properties = getUsedProperties(object);
    for (const auto& property : used_properties) {
      if (object->property(property.toUtf8().data()) != properties[property])
        return false;
    }
  }

  return true;
}

QVariantMap PropertiesSearching::createQuery(QObject* object) const {
  auto query = QVariantMap{};
  auto properties = QVariantMap{};

  const auto used_properties = getUsedProperties(object);
  for (const auto& property : used_properties) {
    if (auto value = object->property(property.toUtf8().data());
        value.isValid()) {
      properties[property] = value;
    }
  }

  query[properties_query] = properties;

  return query;
}

QSet<QString> PropertiesSearching::getUsedProperties(QObject* object) {
  static const auto type_to_properties = getTypeToProperties();

  auto used_properties = QSet<QString>{};

  auto meta_object = object->metaObject();
  while (meta_object) {
    const auto type_id = meta_object->metaType().id();
    const auto type_properties = type_to_properties.find(type_id);

    if (type_properties != type_to_properties.end()) {
      return *type_properties;
    }

    meta_object = meta_object->superClass();
  }

  return used_properties;
}

QMap<int, QSet<QString>> PropertiesSearching::getTypeToProperties() {
#define DEF_PROP(Object, ...)                                  \
  {                                                            \
    qMetaTypeId<Object>(),                                     \
        (QSet<QString>({"objectName", "visible", "enabled"}) + \
         QSet<QString>({__VA_ARGS__}))                         \
  }

  const auto type_to_properties = QMap<int, QSet<QString>>{
      DEF_PROP(QWidget),
      DEF_PROP(QPushButton, "text"),
      DEF_PROP(QLineEdit, "text", "placeholderText"),
      DEF_PROP(QLabel, "text"),
      DEF_PROP(QMenu, "title"),
      DEF_PROP(QCheckBox, "checked", "text"),
      DEF_PROP(QComboBox, "currentText"),
      DEF_PROP(QRadioButton, "checked", "text"),
      DEF_PROP(QAbstractSlider, "value", "maximum", "minimum"),
      DEF_PROP(QProgressBar, "value", "maximum", "minimum"),
      DEF_PROP(QTabWidget, "currentIndex", "count"),
      DEF_PROP(QTableWidget, "rowCount", "columnCount"),
      DEF_PROP(QPlainTextEdit, "plainText"),
  };

#undef DEF_PROP

  return type_to_properties;
}

/* ------------------------------- PathSearching ----------------------------
 */

PathSearching::PathSearching() = default;

PathSearching::~PathSearching() = default;

bool PathSearching::matchesQuery(QObject* object,
                                 const QVariantMap& query) const {
  if (query.contains(path_query)) {
    return getPath(object).contains(query[path_query].toString());
  }

  return true;
}

QVariantMap PathSearching::createQuery(QObject* object) const {
  auto query = QVariantMap{};
  query[path_query] = getPath(object);

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
