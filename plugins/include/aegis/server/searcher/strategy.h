#ifndef AEGIS_SERVER_SEARCHER_STRATEGY_H
#define AEGIS_SERVER_SEARCHER_STRATEGY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLatin1String>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- SearchingStrategy -------------------------- */

class SearchingStrategy {
 public:
  explicit SearchingStrategy();
  virtual ~SearchingStrategy();

  [[nodiscard]] virtual bool matchesQuery(QObject* object,
                                          const QVariantMap& query) const = 0;
  [[nodiscard]] virtual QVariantMap createQuery(QObject* object) const = 0;
};

/* ------------------------------- TypeSearching ---------------------------- */

class TypeSearching : public SearchingStrategy {
  static constexpr QLatin1String TypeQuery = QLatin1String("type");

 public:
  explicit TypeSearching();
  ~TypeSearching() override;

  [[nodiscard]] bool matchesQuery(QObject* object,
                                  const QVariantMap& query) const override;
  [[nodiscard]] QVariantMap createQuery(QObject* object) const override;
};

/* ---------------------------- PropertiesSearching ------------------------- */

class PropertiesSearching : public SearchingStrategy {
  static constexpr QLatin1String PropertiesQuery = QLatin1String("properties");

 public:
  explicit PropertiesSearching();
  ~PropertiesSearching() override;

  [[nodiscard]] bool matchesQuery(QObject* object,
                                  const QVariantMap& query) const override;
  [[nodiscard]] QVariantMap createQuery(QObject* object) const override;
};

/* ------------------------------- PathSearching ---------------------------- */

class PathSearching : public SearchingStrategy {
  static constexpr QLatin1String pathQuery = QLatin1String("path");

 public:
  explicit PathSearching();
  ~PathSearching() override;

  [[nodiscard]] bool matchesQuery(QObject* object,
                                  const QVariantMap& query) const override;
  [[nodiscard]] QVariantMap createQuery(QObject* object) const override;

 private:
  [[nodiscard]] QString getPath(QObject* object) const;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SEARCHER_STRATEGY_H