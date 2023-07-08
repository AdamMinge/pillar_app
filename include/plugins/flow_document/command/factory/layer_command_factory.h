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

  [[nodiscard]] egnite::Command* createSetVisible(FlowDocument* document,
                                                  QList<Object*> objects,

                                                  bool visible) const override;
  [[nodiscard]] egnite::Command* createSetName(FlowDocument* document,
                                               QList<Object*> objects,
                                               QString name) const override;
  [[nodiscard]] egnite::Command* createSetPosition(
      FlowDocument* document, QList<Object*> objects,
      QPointF position) const override;

  [[nodiscard]] egnite::Command* createAddCustomProperties(
      FlowDocument* document, QList<Object*> objects,
      QVariantMap properties) const override;
  [[nodiscard]] egnite::Command* createRemoveCustomProperties(
      FlowDocument* document, QList<Object*> objects,
      QStringList properties) const override;
  [[nodiscard]] egnite::Command* createSetCustomProperty(
      FlowDocument* document, QList<Object*> objects, QString property,
      QVariant value) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_COMMAND_FACTORY_H
