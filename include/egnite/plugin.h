#ifndef EGNITE_PLUGIN_H
#define EGNITE_PLUGIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class PluginImpl;

class LIB_EGNITE_API Plugin {
 public:
  static Plugin create(const QString &plugin_file);
  static Plugin create(QObject *instance);

 public:
  ~Plugin();

  Plugin(Plugin &&other) noexcept;
  Plugin &operator=(Plugin &&other) noexcept;

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getDescription() const;
  [[nodiscard]] QString getVersion() const;
  [[nodiscard]] QString getFileName() const;
  [[nodiscard]] QIcon getIcon() const;

  [[nodiscard]] bool isStatic() const;
  [[nodiscard]] bool isDynamic() const;

  bool enable();
  bool disable();

  [[nodiscard]] bool isEnabled() const;

 protected:
  explicit Plugin(std::unique_ptr<PluginImpl> impl);

 private:
  std::unique_ptr<PluginImpl> m_impl;
};

}  // namespace egnite

#endif  // EGNITE_PLUGIN_H
