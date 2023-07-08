#ifndef FLOW_DOCUMENT_LAYER_COMMAND_FACTORY_H
#define FLOW_DOCUMENT_LAYER_COMMAND_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/factory/object_command_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API LayerCommandFactory : public ObjectCommandFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectCommandFactory)

 public:
  explicit LayerCommandFactory(QObject* parent = nullptr);
  ~LayerCommandFactory() override;

  [[nodiscard]] QString getObjectClassName() const override;

  [[nodiscard]] egnite::Command* createSetVisible(QList<Object*> objects,
                                                  FlowDocument* document,
                                                  bool visible) const override;
  [[nodiscard]] egnite::Command* createSetName(QList<Object*> objects,
                                               FlowDocument* document,
                                               QString name) const override;
  [[nodiscard]] egnite::Command* createSetPosition(
      QList<Object*> objects, FlowDocument* document,
      QPointF position) const override;

  [[nodiscard]] egnite::Command* createAddCustomProperties(
      QList<Object*> objects, FlowDocument* document,
      QVariantMap properties) const override;
  [[nodiscard]] egnite::Command* createRemoveCustomProperties(
      QList<Object*> objects, FlowDocument* document,
      QStringList properties) const override;
  [[nodiscard]] egnite::Command* createSetCustomProperty(
      QList<Object*> objects, FlowDocument* document, QString property,
      QVariant value) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_COMMAND_FACTORY_H
