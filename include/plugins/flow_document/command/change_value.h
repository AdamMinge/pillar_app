#ifndef FLOW_DOCUMENT_CHANGE_VALUE_H
#define FLOW_DOCUMENT_CHANGE_VALUE_H

/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */
#include <QDebug>
namespace flow_document {

class FlowDocument;

template <typename OBJECT, typename VALUE>
class ChangeValue : public egnite::Command {
 public:
  explicit ChangeValue(QString name, FlowDocument* document,
                       QVector<OBJECT*> objects, const VALUE& value,
                       Command* parent = nullptr);
  ~ChangeValue() override;

  [[nodiscard]] bool canMergeWith(const Command& other) const override;
  void mergeWith(const Command& other) override;

  void undo() override;
  void redo() override;

 protected:
  [[nodiscard]] virtual VALUE getValue(const OBJECT* object) const = 0;
  virtual void setValue(OBJECT* object, const VALUE& value) = 0;

  [[nodiscard]] FlowDocument* getDocument() const;
  [[nodiscard]] const QVector<OBJECT*>& getObjects() const;

  [[nodiscard]] QVector<VALUE> getValues() const;
  void setValues(const QVector<VALUE>& values);

 private:
  FlowDocument* m_document;
  QVector<OBJECT*> m_objects;
  QVector<VALUE> m_values;
};

template <typename OBJECT, typename VALUE>
ChangeValue<OBJECT, VALUE>::ChangeValue(QString name, FlowDocument* document,
                                        QVector<OBJECT*> objects,
                                        const VALUE& value, Command* parent)
    : egnite::Command(name, parent),
      m_document(document),
      m_objects(std::move(objects)) {
  m_values.fill(value, m_objects.count());
}

template <typename OBJECT, typename VALUE>
ChangeValue<OBJECT, VALUE>::~ChangeValue() = default;

template <typename OBJECT, typename VALUE>
bool ChangeValue<OBJECT, VALUE>::canMergeWith(const Command& other) const {
  auto& change_event = static_cast<const ChangeValue<OBJECT, VALUE>&>(other);
  if (m_document != change_event.m_document) return false;
  if (m_objects != change_event.m_objects) return false;

  return true;
}

template <typename OBJECT, typename VALUE>
void ChangeValue<OBJECT, VALUE>::mergeWith(const Command& other) {
  setObsolete(getValues() == m_values);
}

template <typename OBJECT, typename VALUE>
void ChangeValue<OBJECT, VALUE>::undo() {
  setValues(std::exchange(m_values, getValues()));
}

template <typename OBJECT, typename VALUE>
void ChangeValue<OBJECT, VALUE>::redo() {
  setValues(std::exchange(m_values, getValues()));
}

template <typename OBJECT, typename VALUE>
FlowDocument* ChangeValue<OBJECT, VALUE>::getDocument() const {
  return m_document;
}

template <typename OBJECT, typename VALUE>
const QVector<OBJECT*>& ChangeValue<OBJECT, VALUE>::getObjects() const {
  return m_objects;
}

template <typename OBJECT, typename VALUE>
QVector<VALUE> ChangeValue<OBJECT, VALUE>::getValues() const {
  QVector<VALUE> values;
  values.reserve(m_objects.size());
  for (const auto object : m_objects) values.append(getValue(object));
  return values;
}

template <typename OBJECT, typename VALUE>
void ChangeValue<OBJECT, VALUE>::setValues(const QVector<VALUE>& values) {
  Q_ASSERT(m_objects.size() == values.size());
  for (auto i = m_objects.size() - 1; i >= 0; --i)
    setValue(m_objects.at(i), values.at(i));
}

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_VALUE_H
