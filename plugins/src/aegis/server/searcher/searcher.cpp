/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>
/* --------------------------------- Standard ------------------------------- */
#include <queue>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/searcher/searcher.h"
#include "aegis/server/searcher/strategy.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

ObjectSearcher::ObjectSearcher() {
  m_searching_strategies.emplace_back(std::make_unique<TypeSearching>());
  m_searching_strategies.emplace_back(std::make_unique<PropertiesSearching>());
  m_searching_strategies.emplace_back(std::make_unique<PathSearching>());
}

ObjectSearcher::~ObjectSearcher() = default;

QObject* ObjectSearcher::getObject(const QString& id) {
  const auto query = createQuery(id);
  const auto object = findObject(query);

  return object;
}

QString ObjectSearcher::getId(QObject* object) {
  auto query = QVariantMap{};
  for (const auto& searching_strategy : m_searching_strategies) {
    const auto sub_query = searching_strategy->createQuery(object);
    query.insert(sub_query);
  }

  return createId(query);
}

QVariantMap ObjectSearcher::createQuery(const QString& id) const {
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

QString ObjectSearcher::createId(const QVariantMap& query) const {
  auto json_object = QJsonObject{};
  for (auto it = query.begin(); it != query.end(); ++it) {
    json_object.insert(it.key(), QJsonValue::fromVariant(it.value()));
  }

  const auto json_document = QJsonDocument(json_object);
  return QString(json_document.toJson(QJsonDocument::Compact));
}

QObject* ObjectSearcher::ObjectSearcher::findObject(const QVariantMap& query) {
  const auto top_widgets = qApp->topLevelWidgets();
  auto objects = std::queue<QObject*>{};
  for (auto top_widget : top_widgets) {
    objects.push(top_widget);
  }

  while (!objects.empty()) {
    auto parent = objects.front();
    objects.pop();

    const auto matches_query = std::all_of(
        m_searching_strategies.begin(), m_searching_strategies.end(),
        [parent, &query](const auto& searching_strategy) {
          return searching_strategy->matchesQuery(parent, query);
        });

    if (matches_query) return parent;

    for (const auto child : parent->children()) {
      objects.push(child);
    }
  }

  return nullptr;
}

}  // namespace aegis
