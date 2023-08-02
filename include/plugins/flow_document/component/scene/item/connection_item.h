#ifndef FLOW_DOCUMENT_CONNECTION_ITEM_H
#define FLOW_DOCUMENT_CONNECTION_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeItem;
class Connection;
class ConnectionItem;
class NodesChangeEvent;
class ConnectionsChangeEvent;

/* -------------------------- ConnectionGeometry ------------------------ */

class FLOW_DOCUMENT_API ConnectionGeometry {
  using PointsPair = std::pair<QPointF, QPointF>;

 public:
  explicit ConnectionGeometry(const ConnectionItem& connection_item);
  ~ConnectionGeometry();

  [[nodiscard]] QRectF getBoundingRect() const;
  [[nodiscard]] QPainterPath getCubicPath() const;

  [[nodiscard]] const PointsPair& getConnectionPoints() const;
  [[nodiscard]] const PointsPair& getControlPoints() const;

  void recalculate();

 private:
  [[nodiscard]] PointsPair calculateConnectionPoints() const;
  [[nodiscard]] PointsPair calculateControlPoints() const;

 private:
  const ConnectionItem& m_connection_item;
  PointsPair m_connection_points;
  PointsPair m_control_points;
};

/* --------------------------- ConnectionPainter ------------------------ */

class FLOW_DOCUMENT_API ConnectionPainter {
 public:
  explicit ConnectionPainter(const ConnectionItem& connection_item);
  virtual ~ConnectionPainter();

  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option);

 private:
  const ConnectionItem& m_connection_item;
};

/* ----------------------------- ConnectionItem ------------------------- */

class FLOW_DOCUMENT_API ConnectionItem : public ObjectItem {
  Q_OBJECT

 public:
  explicit ConnectionItem(Connection* flow, FlowDocument* document,
                          QGraphicsItem* parent = nullptr);
  ~ConnectionItem() override;

  [[nodiscard]] Connection* getConnection() const;

  [[nodiscard]] NodeItem* getOutNodeItem() const;
  [[nodiscard]] NodeItem* getInNodeItem() const;

  [[nodiscard]] const ConnectionPainter& getPainter() const;
  [[nodiscard]] const ConnectionGeometry& getGeometry() const;

  [[nodiscard]] QRectF boundingRect() const override;
  [[nodiscard]] QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

 private Q_SLOTS:
  void onSceneChanged() override;
  void onEvent(const ChangeEvent& event) override;
  void onUpdate(const ConnectionsChangeEvent& event);
  void onUpdate(const NodesChangeEvent& event);

  void updateConnection();
  void updateGeometry();
  void updateVisibility();

 private:
  ConnectionPainter m_connection_painter;
  ConnectionGeometry m_connection_geometry;

  NodeItem* m_out_node_item;
  NodeItem* m_in_node_item;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_ITEM_H
