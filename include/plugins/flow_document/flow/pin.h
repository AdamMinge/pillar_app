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

  [[nodiscard]] const QVariant &getData() const;
  [[nodiscard]] const QString &getCaption() const;

  void setData(QVariant data);
  void setCaption(QString caption);

  void addListener(Listener &&listener);
  void clearListeners();

 private:
  void dataChangeNotify();

 private:
  QVariant m_data;
  QString m_caption;
  QList<Listener> m_listeners;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PIN_H