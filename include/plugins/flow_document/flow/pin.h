#ifndef FLOW_DOCUMENT_PIN_H
#define FLOW_DOCUMENT_PIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QVariant>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Pin {
 public:
  enum class Type { In, Out };

  using Listener = std::function<void(const QVariant &)>;

 public:
  explicit Pin(QVariant data, QString caption);
  ~Pin();

  Pin(const Pin &other);
  Pin(Pin &&other);

  Pin &operator=(const Pin &other);
  Pin &operator=(Pin &&other);

  [[nodiscard]] const QVariant &getData() const;
  [[nodiscard]] const QString &getCaption() const;

  void setData(QVariant data);
  void setCaption(QString caption);

  void addListener(const size_t &id, Listener &&listener);
  void removeListener(const size_t &id);
  void clearListeners();

 private:
  void dataChangeNotify();

 private:
  QVariant m_data;
  QString m_caption;
  std::map<size_t, Listener> m_listeners;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PIN_H