/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/factory/layer_command_factory.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/flow/layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Utils -------------------------------- */

namespace {

QList<Layer*> toLayers(QList<Object*>&& objects) {
  QList<Layer*> layers;
  std::transform(std::make_move_iterator(objects.begin()),
                 std::make_move_iterator(objects.end()),
                 std::back_inserter(layers), [](Object* object) {
                   Q_ASSERT(object->isClassOrChild<Layer>());
                   return static_cast<Layer*>(object);
                 });

  return layers;
}

}  // namespace

/* ----------------------------- NodeCommandFactory ------------------------- */

LayerCommandFactory::LayerCommandFactory(QObject* parent)
    : ObjectCommandFactory(parent) {}

LayerCommandFactory::~LayerCommandFactory() = default;

QString LayerCommandFactory::getObjectClassName() const {
  return Layer::sGetClassName();
}

egnite::Command* LayerCommandFactory::createSetVisible(FlowDocument* document,
                                                       QList<Object*> objects,
                                                       bool visible) const {
  return new SetLayersVisible(document, toLayers(std::move(objects)), visible);
}

egnite::Command* LayerCommandFactory::createSetName(FlowDocument* document,
                                                    QList<Object*> objects,
                                                    QString name) const {
  return new SetLayersName(document, toLayers(std::move(objects)),
                           std::move(name));
}

egnite::Command* LayerCommandFactory::createSetPosition(
    FlowDocument* document, QList<Object*> objects, QPointF position) const {
  return new SetLayersPosition(document, toLayers(std::move(objects)),
                               std::move(position));
}

egnite::Command* LayerCommandFactory::createAddCustomProperties(
    FlowDocument* document, QList<Object*> objects,
    QVariantMap properties) const {
  return new AddLayersProperties(document, toLayers(std::move(objects)),
                                 std::move(properties));
}

egnite::Command* LayerCommandFactory::createRemoveCustomProperties(
    FlowDocument* document, QList<Object*> objects,
    QStringList properties) const {
  return new RemoveLayersProperties(document, toLayers(std::move(objects)),
                                    std::move(properties));
}

egnite::Command* LayerCommandFactory::createSetCustomProperty(
    FlowDocument* document, QList<Object*> objects, QString property,
    QVariant value) const {
  return new SetLayersCustomProperty(document, toLayers(std::move(objects)),
                                     std::move(property), std::move(value));
}

}  // namespace flow_document
