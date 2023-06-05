#ifndef FLOW_DOCUMENT_PROPERTIES_BROWSER_H
#define FLOW_DOCUMENT_PROPERTIES_BROWSER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/property_browser/tree_property_browser.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class ChangeEvent;
class Object;

class ObjectPropertiesFactory;
class ObjectProperties;

class FLOW_DOCUMENT_API PropertiesBrowser
    : public utils::QtTreePropertyBrowser,
      public egnite::PluginListener<ObjectPropertiesFactory> {
  Q_OBJECT

 public:
  explicit PropertiesBrowser(QWidget* parent = nullptr);
  ~PropertiesBrowser() override;

  void setDocument(FlowDocument* document);
  [[nodiscard]] FlowDocument* getDocument() const;

  void setFilter(const QString& filter);
  [[nodiscard]] QString getFilter() const;

  [[nodiscard]] QAction* getAddPropertyAction() const;
  [[nodiscard]] QAction* getRemovePropertyAction() const;

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override;
  void changeEvent(QEvent* event) override;

  void addedObject(ObjectPropertiesFactory* factory) override;
  void removedObject(ObjectPropertiesFactory* factory) override;

 private Q_SLOTS:
  void onCurrentObjectChanged(Object* object);

  void onAddProperty();
  void onRemoveProperty();

  void updateActions();

 private:
  void initBrowser();
  void initConnections();
  void retranslateUi();

  void filterProperties();
  bool filterProperty(utils::QtBrowserItem* item);

  [[nodiscard]] ObjectPropertiesFactory* getFactoryByObject(Object* object);
  [[nodiscard]] ObjectProperties* getPropertiesByObject(Object* object);

 private:
  FlowDocument* m_document;
  QString m_filter;

  ObjectProperties* m_current_properties;
  QList<ObjectPropertiesFactory*> m_properties_factories;
  QHash<ObjectPropertiesFactory*, ObjectProperties*> m_factories_to_properties;

  QAction* m_add_property;
  QAction* m_remove_property;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PROPERTIES_BROWSER_H
