/* ----------------------------------- Local -------------------------------- */
#include "flow/factory/shape_factory.h"
/* -------------------------------------------------------------------------- */

ShapeFactory::ShapeFactory(QString name, QString section, QObject* parent)
    : ShapeFactory(std::move(name), std::move(section), QIcon(), parent) {}

ShapeFactory::ShapeFactory(QString name, QString section, QIcon icon,
                           QObject* parent)
    : ObjectFactory(type, std::move(name), std::move(section), std::move(icon),
                    parent) {}

ShapeFactory::~ShapeFactory() = default;