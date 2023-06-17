#ifndef FLOW_DOCUMENT_GROUP_FACTORY_H
#define FLOW_DOCUMENT_GROUP_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/factory/factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API GroupFactory : public Factory {
  Q_OBJECT

 public:
  using Factories = std::vector<std::unique_ptr<Factory>>;

 public:
  explicit GroupFactory(QString name);
  ~GroupFactory() override;

  void append(std::unique_ptr<Factory> factory);
  void insert(qsizetype index, std::unique_ptr<Factory> factory);
  void remove(qsizetype index);

  [[nodiscard]] std::unique_ptr<Factory> take(qsizetype index);
  [[nodiscard]] Factory* at(qsizetype index) const;
  [[nodiscard]] qsizetype indexOf(Factory* factory) const;

  [[nodiscard]] qsizetype size() const;

  Factories::iterator begin();
  Factories::iterator end();

  Factories::const_iterator begin() const;
  Factories::const_iterator end() const;

 private:
  Factories m_factories;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::GroupFactory, "org.flow.GroupFactory")

#endif  // FLOW_DOCUMENT_GROUP_FACTORY_H