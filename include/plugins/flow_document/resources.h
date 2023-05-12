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

#define _DEFINE_ICON(name, size, icon) \
  constexpr QLatin1String name{":/plugins/flow_document/images/" size "/" icon};

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
_DEFINE_ICON(GroupLayer, "16x16", "group_layer.png")
_DEFINE_ICON(NodeLayer, "16x16", "node_layer.png")

}  // namespace x16

namespace x32 {

_DEFINE_ICON(Dir, "32x32", "dir.png")
_DEFINE_ICON(GroupLayer, "32x32", "group_layer.png")
_DEFINE_ICON(NodeLayer, "32x32", "node_layer.png")
_DEFINE_ICON(Node, "32x32", "node.png")
_DEFINE_ICON(SelectionTool, "32x32", "selection_tool.png")

}  // namespace x32

namespace x64 {

_DEFINE_ICON(FlowDocument, "64x64", "flow_document.png")

}  // namespace x64

}  // namespace icons

/* ----------------------------------- Styles ------------------------------- */

namespace styles {

#define _DEFINE_STYLE(name, style) \
  constexpr QLatin1String name{":/plugins/flow_document/styles/" style};

_DEFINE_STYLE(Default, "default.png")

}  // namespace styles

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_RESOURCES_H
