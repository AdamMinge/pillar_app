#ifndef AEGIS_SERVER_SEARCHER_SEARCHER_H
#define AEGIS_SERVER_SEARCHER_SEARCHER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <map>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class SearchingStrategy;

/* ------------------------------- ObjectSearcher --------------------------- */

class ObjectSearcher {
 public:
  explicit ObjectSearcher();
  ~ObjectSearcher();

  [[nodiscard]] QObject* getObject(const QString& id);
  [[nodiscard]] QString getId(QObject* object);

 private:
  [[nodiscard]] QVariantMap createQuery(const QString& id) const;
  [[nodiscard]] QString createId(const QVariantMap& query) const;

  [[nodiscard]] QObject* findObject(const QVariantMap& query);

 private:
  std::list<std::unique_ptr<SearchingStrategy>> m_searching_strategies;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SEARCHER_SEARCHER_H