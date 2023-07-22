#ifndef FLOW_DOCUMENT_RESOURCES_H
#define FLOW_DOCUMENT_RESOURCES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLatin1String>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Icons -------------------------------- */

namespace icons {

#define _DEFINE_ICON(NAME, SIZE, ICON) \
  constexpr QLatin1String NAME{":/plugins/flow_document/images/" SIZE "/" ICON};

namespace x16 {

_DEFINE_ICON(Add, "16x16", "add.png")
_DEFINE_ICON(Down, "16x16", "down.png")
_DEFINE_ICON(Duplicate, "16x16", "duplicate.png")
_DEFINE_ICON(Hidden, "16x16", "hidden.png")
_DEFINE_ICON(Locked, "16x16", "locked.png")
_DEFINE_ICON(Remove, "16x16", "remove.png")
_DEFINE_ICON(ShowHideOthers, "16x16", "show_hide_others.png")
_DEFINE_ICON(Unlocked, "16x16", "unlocked.png")
_DEFINE_ICON(Up, "16x16", "up.png")
_DEFINE_ICON(Visible, "16x16", "visible.png")

}  // namespace x16

namespace x32 {

_DEFINE_ICON(Group, "32x32", "group.png")
_DEFINE_ICON(Layer, "32x32", "layer.png")
_DEFINE_ICON(NodeLayer, "32x32", "node_layer.png")
_DEFINE_ICON(ConnectionLayer, "32x32", "connection_layer.png")
_DEFINE_ICON(Node, "32x32", "node.png")
_DEFINE_ICON(SelectionTool, "32x32", "selection_tool.png")

}  // namespace x32

namespace x64 {

_DEFINE_ICON(FlowDocument, "64x64", "flow_document.png")

}  // namespace x64

}  // namespace icons

/* ----------------------------------- Styles ------------------------------- */

namespace styles {

#define _DEFINE_STYLE(NAME, STYLE) \
  constexpr QLatin1String NAME{":/plugins/flow_document/styles/" STYLE};

_DEFINE_STYLE(Default, "default.json")

}  // namespace styles

/* -------------------------------- Translations ---------------------------- */

namespace translations {

constexpr QLatin1String TranslationsPath{
    ":/plugins/flow_document/translations"};

}  // namespace translations

/* ---------------------------------- MimeType ------------------------------ */

namespace mimetype {

constexpr QLatin1String Layers = QLatin1String("application/vnd.layer.list");

constexpr QLatin1String Factories =
    QLatin1String("application/vnd.factory.list");

}  // namespace mimetype

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_RESOURCES_H
