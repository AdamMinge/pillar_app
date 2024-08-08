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

/* ------------------------------- SearcherManager -------------------------- */

class SearcherManager {
 public:
  [[nodiscard]] static SearcherManager& getInstance();
  static void deleteInstance();

 public:
  ~SearcherManager();

  [[nodiscard]] QObject* getObject(const QString& id) const;
  [[nodiscard]] QList<QObject*> getObjects(const QString& id) const;

  [[nodiscard]] QString getId(QObject* object) const;

 protected:
  explicit SearcherManager();

 private:
  [[nodiscard]] QVariantMap createQuery(const QString& id) const;
  [[nodiscard]] QString createId(const QVariantMap& query) const;

  [[nodiscard]] QList<QObject*> findObjects(
      const QVariantMap& query,
      qsizetype limit = std::numeric_limits<qsizetype>::max()) const;

 private:
  static std::unique_ptr<SearcherManager> m_instance;

  std::list<std::unique_ptr<SearchingStrategy>> m_searching_strategies;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SEARCHER_SEARCHER_H