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

/* ---------------------------------- ObjectQuery --------------------------- */

class ObjectQuery {
  friend class Searcher;
  friend class CommonQueries;

 public:
  [[nodiscard]] static ObjectQuery fromString(const QString& id);

 public:
  explicit ObjectQuery();
  ~ObjectQuery();

  [[nodiscard]] QString toString() const;
  [[nodiscard]] bool isValid() const;

 protected:
  explicit ObjectQuery(QVariantMap data);

 private:
  QVariantMap m_data;
};

/* --------------------------------- CommonQueries -------------------------- */

class CommonQueries {
 public:
  [[nodiscard]] static ObjectQuery createPathQuery(const QString& path);
  [[nodiscard]] static ObjectQuery createTypeQuery(const QMetaType& type);
  [[nodiscard]] static ObjectQuery createPropertiesQuery(
      const QVariantMap& properties);
};

/* ----------------------------------- Searcher ----------------------------- */

class Searcher : public QObject {
  Q_OBJECT

 public:
  explicit Searcher(QObject* parent = nullptr);
  ~Searcher() override;

  [[nodiscard]] QObject* getObject(const ObjectQuery& query) const;
  [[nodiscard]] QList<QObject*> getObjects(const ObjectQuery& query) const;

  [[nodiscard]] ObjectQuery getId(QObject* object) const;

 private:
  [[nodiscard]] QList<QObject*> findObjects(
      const ObjectQuery& query,
      qsizetype limit = std::numeric_limits<qsizetype>::max()) const;

 private:
  std::list<std::unique_ptr<SearchingStrategy>> m_searching_strategies;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SEARCHER_SEARCHER_H