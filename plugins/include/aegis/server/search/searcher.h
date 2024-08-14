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

/* ----------------------------------- Searcher ----------------------------- */

class Searcher : public QObject {
  Q_OBJECT

 public:
  explicit Searcher(QObject* parent = nullptr);
  ~Searcher() override;

  [[nodiscard]] QObject* getObject(const QString& id) const;
  [[nodiscard]] QList<QObject*> getObjects(const QString& id) const;

  [[nodiscard]] QString getId(QObject* object) const;

 protected:
 private:
  [[nodiscard]] QVariantMap createQuery(const QString& id) const;
  [[nodiscard]] QString createId(const QVariantMap& query) const;

  [[nodiscard]] QList<QObject*> findObjects(
      const QVariantMap& query,
      qsizetype limit = std::numeric_limits<qsizetype>::max()) const;

 private:
  std::list<std::unique_ptr<SearchingStrategy>> m_searching_strategies;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SEARCHER_SEARCHER_H