/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/item_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- ItemFactory ----------------------------- */

ItemFactory::ItemFactory(QObject* parent) : QObject(parent) {}

ItemFactory::~ItemFactory() = default;

}  // namespace flow_document