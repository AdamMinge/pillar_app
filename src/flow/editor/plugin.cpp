/* ------------------------------------ Qt ---------------------------------- */
#include <QPluginLoader>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/plugin.h"
#include "flow/editor/plugin_manager.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Plugin Impl ----------------------------- */

class PluginImpl
{
public:
  explicit PluginImpl() = default;
  virtual ~PluginImpl() = default;

  [[nodiscard]] virtual QString getFileName() const = 0;
  [[nodiscard]] virtual bool isStatic() const = 0;
  [[nodiscard]] bool isDynamic() const;

  virtual bool enable() = 0;
  virtual bool disable() = 0;

  [[nodiscard]] virtual bool isEnabled() const = 0;
};

bool PluginImpl::isDynamic() const { return !isStatic(); }

/* ---------------------------- Dynamic Plugin Impl ------------------------- */

class DynamicPluginImpl : public PluginImpl
{
public:
  explicit DynamicPluginImpl(
    std::unique_ptr<QPluginLoader> loader, QString file_name);
  ~DynamicPluginImpl() override;

  [[nodiscard]] QString getFileName() const override;
  [[nodiscard]] bool isStatic() const override;

  bool enable() override;
  bool disable() override;

  [[nodiscard]] bool isEnabled() const override;

private:
  std::unique_ptr<QPluginLoader> m_loader;
  QString m_file_name;
  QObject *m_instance;
};

DynamicPluginImpl::DynamicPluginImpl(
  std::unique_ptr<QPluginLoader> loader, QString file_name)
    : m_loader(std::move(loader)), m_file_name(std::move(file_name)),
      m_instance(nullptr)
{}

DynamicPluginImpl::~DynamicPluginImpl() = default;

QString DynamicPluginImpl::getFileName() const { return m_file_name; }

bool DynamicPluginImpl::isStatic() const { return false; }

bool DynamicPluginImpl::enable()
{
  if (isEnabled()) return true;

  m_instance = m_loader->instance();
  if (!m_instance) return false;

  PluginManager::getInstance().addObject(m_instance);
  return true;
}

bool DynamicPluginImpl::disable()
{
  if (!isEnabled()) return true;

  PluginManager::getInstance().removeObject(m_instance);

  m_instance = nullptr;
  return m_loader->unload();
}

bool DynamicPluginImpl::isEnabled() const { return m_instance != nullptr; }

/* ----------------------------- Static Plugin Impl ------------------------- */

class StaticPluginImpl : public PluginImpl
{
public:
  explicit StaticPluginImpl(QObject *instance);
  ~StaticPluginImpl() override;

  [[nodiscard]] QString getFileName() const override;
  [[nodiscard]] bool isStatic() const override;

  bool enable() override;
  bool disable() override;

  [[nodiscard]] bool isEnabled() const override;

private:
  QObject *m_instance;
};

StaticPluginImpl::StaticPluginImpl(QObject *instance) : m_instance(instance) {}

StaticPluginImpl::~StaticPluginImpl() = default;

QString StaticPluginImpl::getFileName() const { return QLatin1String{}; }

bool StaticPluginImpl::isStatic() const { return true; }

bool StaticPluginImpl::enable()
{
  if (!isEnabled()) PluginManager::getInstance().addObject(m_instance);
  return true;
}

bool StaticPluginImpl::disable()
{
  if (isEnabled()) PluginManager::getInstance().removeObject(m_instance);
  return true;
}

bool StaticPluginImpl::isEnabled() const
{
  return PluginManager::getInstance().getObjects<QObject>().contains(
    m_instance);
}

/* ----------------------------------- Plugin ------------------------------- */


Plugin Plugin::create(const QString &plugin_file)
{
  auto loader = std::make_unique<QPluginLoader>(plugin_file);
  auto impl =
    std::make_unique<DynamicPluginImpl>(std::move(loader), plugin_file);
  return Plugin(std::move(impl));
}

Plugin Plugin::create(QObject *instance)
{
  auto impl = std::make_unique<StaticPluginImpl>(instance);
  return Plugin(std::move(impl));
}

Plugin::Plugin(std::unique_ptr<PluginImpl> impl) : m_impl(std::move(impl)) {}

Plugin::~Plugin()
{
  if (isEnabled()) disable();
}

QString Plugin::getFileName() const
{
  return m_impl ? m_impl->getFileName() : QString{};
}

bool Plugin::isStatic() const { return m_impl && m_impl->isStatic(); }

bool Plugin::isDynamic() const { return m_impl && m_impl->isDynamic(); }

Plugin::Plugin(Plugin &&other) noexcept = default;

Plugin &Plugin::operator=(Plugin &&other) noexcept = default;

bool Plugin::enable() { return m_impl && m_impl->enable(); }

bool Plugin::disable() { return m_impl && m_impl->disable(); }

bool Plugin::isEnabled() const { return m_impl && m_impl->isEnabled(); }