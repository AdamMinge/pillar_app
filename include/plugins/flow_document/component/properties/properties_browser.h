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

class ObjectProperties;

class FLOW_DOCUMENT_API PropertiesBrowser
    : public utils::QtTreePropertyBrowser,
      public egnite::PluginListener<ObjectProperties> {
  Q_OBJECT

 public:
  explicit PropertiesBrowser(QWidget* parent = nullptr);
  ~PropertiesBrowser() override;

  void setDocument(FlowDocument* document);
  [[nodiscard]] FlowDocument* getDocument() const;

  void setFilter(const QString& filter);
  [[nodiscard]] QString getFilter() const;

 protected:
  void changeEvent(QEvent* event) override;

  void addedObject(ObjectProperties* object_properties) override;
  void removedObject(ObjectProperties* object_properties) override;

 private Q_SLOTS:
  void onEvent(const ChangeEvent& event);
  void onCurrentObjectChanged(Object* object);

 private:
  void initBrowser();
  void initConnections();
  void retranslateUi();

  void filterProperties();
  bool filterProperty(utils::QtBrowserItem* item);

  [[nodiscard]] ObjectProperties* getPropertiesByObject(Object* object) const;

 private:
  FlowDocument* m_document;

  QString m_filter;
  ObjectProperties* m_current_properties;
  QHash<QString, ObjectProperties*> m_class_to_properties;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PROPERTIES_BROWSER_H
