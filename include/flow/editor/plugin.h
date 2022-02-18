#ifndef FLOW_PLUGIN_H
#define FLOW_PLUGIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class PluginImpl;

class Plugin
{
public:
  static Plugin create(const QString &plugin_file);
  static Plugin create(QObject *instance);

public:
  ~Plugin();

  Plugin(Plugin &&other) noexcept;
  Plugin &operator=(Plugin &&other) noexcept;

  [[nodiscard]] QString getFileName() const;
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

#endif//FLOW_PLUGIN_H
