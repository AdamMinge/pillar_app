#ifndef FLOW_DOCUMENT_CHANGE_CONNECTION_H
#define FLOW_DOCUMENT_CHANGE_CONNECTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_value.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Connection;

/* --------------------------- SetConnectionsVisible ------------------------ */

class FLOW_DOCUMENT_API SetConnectionsVisible
    : public ChangeValue<Connection, bool> {
 public:
  explicit SetConnectionsVisible(FlowDocument* document,
                                 QList<Connection*> connections, bool visible,
                                 Command* parent = nullptr);
  ~SetConnectionsVisible() override;

 protected:
  [[nodiscard]] bool getValue(const Connection* connection) const override;
  void setValue(Connection* connection, const bool& visible) override;
};

/* ---------------------------- SetConnectionsName -------------------------- */

class FLOW_DOCUMENT_API SetConnectionsName
    : public ChangeValue<Connection, QString> {
 public:
  explicit SetConnectionsName(FlowDocument* document,
                              QList<Connection*> connections, QString name,
                              Command* parent = nullptr);
  ~SetConnectionsName() override;

 protected:
  [[nodiscard]] QString getValue(const Connection* connection) const override;
  void setValue(Connection* connection, const QString& name) override;
};

/* ----------------------- SetConnectionsCustomProperty --------------------- */

class FLOW_DOCUMENT_API SetConnectionsCustomProperty
    : public ChangeValue<Connection, QVariant> {
 public:
  explicit SetConnectionsCustomProperty(FlowDocument* document,
                                        QList<Connection*> connections,
                                        QString property, QVariant value,
                                        Command* parent = nullptr);
  ~SetConnectionsCustomProperty() override;

 protected:
  [[nodiscard]] QVariant getValue(const Connection* connection) const override;
  void setValue(Connection* connection, const QVariant& value) override;

 private:
  QString m_property;
};

/* ---------------------- AddRemoveConnectionsProperties -------------------- */

class FLOW_DOCUMENT_API AddRemoveConnectionsProperties
    : public pillar::Command {
 public:
  explicit AddRemoveConnectionsProperties(QString name, FlowDocument* document,
                                          QList<Connection*> connections,
                                          QVariantMap properties,
                                          Command* parent = nullptr);
  ~AddRemoveConnectionsProperties() override;

 protected:
  void addProperties();
  void removeProperties();

 protected:
  FlowDocument* m_document;
  QList<Connection*> m_connections;
  QVariantMap m_properties;
};

/* ------------------------- AddConnectionsProperties ----------------------- */

class FLOW_DOCUMENT_API AddConnectionsProperties
    : public AddRemoveConnectionsProperties {
 public:
  explicit AddConnectionsProperties(FlowDocument* document,
                                    QList<Connection*> connections,
                                    QVariantMap properties,
                                    Command* parent = nullptr);
  ~AddConnectionsProperties() override;

  void undo() override;
  void redo() override;
};

/* ------------------------ RemoveConnectionsProperties --------------------- */

class FLOW_DOCUMENT_API RemoveConnectionsProperties
    : public AddRemoveConnectionsProperties {
 public:
  explicit RemoveConnectionsProperties(FlowDocument* document,
                                       QList<Connection*> connections,
                                       QStringList properties,
                                       Command* parent = nullptr);
  ~RemoveConnectionsProperties() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_CONNECTION_H