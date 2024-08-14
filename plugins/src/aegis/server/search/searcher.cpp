/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>
/* --------------------------------- Standard ------------------------------- */
#include <queue>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/search/searcher.h"
#include "aegis/server/search/strategy.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------------- Searcher ----------------------------- */

Searcher::Searcher(QObject* parent) : QObject(parent) {
  m_searching_strategies.emplace_back(std::make_unique<TypeSearching>());
  m_searching_strategies.emplace_back(std::make_unique<PropertiesSearching>());
  m_searching_strategies.emplace_back(std::make_unique<PathSearching>());
}

Searcher::~Searcher() = default;

QObject* Searcher::getObject(const QString& id) const {
  const auto query = createQuery(id);
  const auto objects = findObjects(query, 1);

  return objects.empty() ? nullptr : objects.first();
}

QList<QObject*> Searcher::getObjects(const QString& id) const {
  const auto query = createQuery(id);
  const auto objects = findObjects(query);

  return objects;
}

QString Searcher::getId(QObject* object) const {
  auto query = QVariantMap{};
  for (const auto& searching_strategy : m_searching_strategies) {
    const auto sub_query = searching_strategy->createQuery(object);
    query.insert(sub_query);
  }

  return createId(query);
}

QVariantMap Searcher::createQuery(const QString& id) const {
  auto query = QVariantMap{};

  auto parser_error = QJsonParseError{};
  const auto json_document =
      QJsonDocument::fromJson(id.toUtf8(), &parser_error);

  if (parser_error.error == QJsonParseError::NoError) {
    const auto json_object = json_document.object();

    for (auto it = json_object.begin(); it != json_object.end(); ++it) {
      query.insert(it.key(), it.value().toVariant());
    }
  }

  return query;
}

QString Searcher::createId(const QVariantMap& query) const {
  auto json_object = QJsonObject{};
  for (auto it = query.begin(); it != query.end(); ++it) {
    json_object.insert(it.key(), QJsonValue::fromVariant(it.value()));
  }

  const auto json_document = QJsonDocument(json_object);
  return QString(json_document.toJson(QJsonDocument::Compact));
}

QList<QObject*> Searcher::findObjects(const QVariantMap& query,
                                      qsizetype limit) const {
  const auto top_widgets = qApp->topLevelWidgets();
  auto objects = std::queue<QObject*>{};
  for (auto top_widget : top_widgets) {
    objects.push(top_widget);
  }

  auto found_objects = QList<QObject*>{};
  while (!objects.empty() && found_objects.size() <= limit) {
    auto parent = objects.front();
    objects.pop();

    const auto matches_query = std::all_of(
        m_searching_strategies.begin(), m_searching_strategies.end(),
        [parent, &query](const auto& searching_strategy) {
          return searching_strategy->matchesQuery(parent, query);
        });

    if (matches_query) {
      found_objects.push_back(parent);
    }

    for (const auto child : parent->children()) {
      objects.push(child);
    }
  }

  return found_objects;
}

}  // namespace aegis
