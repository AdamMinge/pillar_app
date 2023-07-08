#ifndef FLOW_DOCUMENT_OBJECT_COMMAND_FACTORY_H
#define FLOW_DOCUMENT_OBJECT_COMMAND_FACTORY_H

/* ------------------------------------- Qt --------------------------------- */
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>
/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Object;

/* ---------------------------- ObjectCommandFactory ------------------------ */

class FLOW_DOCUMENT_API ObjectCommandFactory : public QObject {
  Q_OBJECT

 public:
  explicit ObjectCommandFactory(QObject* parent = nullptr);
  virtual ~ObjectCommandFactory();

  [[nodiscard]] virtual QString getObjectClassName() const = 0;

  [[nodiscard]] virtual egnite::Command* createSetVisible(
      QList<Object*> objects, FlowDocument* document, bool visible) const = 0;
  [[nodiscard]] virtual egnite::Command* createSetName(QList<Object*> objects,
                                                       FlowDocument* document,
                                                       QString name) const = 0;
  [[nodiscard]] virtual egnite::Command* createSetPosition(
      QList<Object*> objects, FlowDocument* document,
      QPointF position) const = 0;

  [[nodiscard]] virtual egnite::Command* createAddCustomProperties(
      QList<Object*> objects, FlowDocument* document,
      QVariantMap properties) const = 0;
  [[nodiscard]] virtual egnite::Command* createRemoveCustomProperties(
      QList<Object*> objects, FlowDocument* document,
      QStringList properties) const = 0;
  [[nodiscard]] virtual egnite::Command* createSetCustomProperty(
      QList<Object*> objects, FlowDocument* document, QString property,
      QVariant value) const = 0;
};

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] ObjectCommandFactory* getObjectCommandFactoryByObject(
    Object* object);

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ObjectCommandFactory,
                    "org.flow.ObjectCommandFactory")

#endif  // FLOW_DOCUMENT_OBJECT_COMMAND_FACTORY_H
