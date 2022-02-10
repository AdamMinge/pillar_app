#ifndef FLOW_INTERFACE_FILE_FORMAT_H
#define FLOW_INTERFACE_FILE_FORMAT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/api/export.h"
/* -------------------------------------------------------------------------- */

namespace api
{

  class API_API IFileFormat : public QObject
  {
    Q_OBJECT

  public:
    enum class Capability;
    Q_DECLARE_FLAGS(Capabilities, Capability);

  public:
    explicit IFileFormat(QObject *parent = nullptr);
    ~IFileFormat() override;

    [[nodiscard]] bool hasCapabilities(Capabilities capabilities) const;
    [[nodiscard]] virtual Capabilities getCapabilities() const;

    [[nodiscard]] virtual QString getNameFilter() const = 0;
    [[nodiscard]] virtual QString getShortName() const = 0;
    [[nodiscard]] virtual bool supportsFile(const QString &filename) const = 0;
  };

  enum class IFileFormat::Capability
  {
    NoCapability = 0x0,
    Read = 0x1,
    Write = 0x2,
    ReadWrite = Read | Write
  };

}// namespace api

Q_DECLARE_OPERATORS_FOR_FLAGS(api::IFileFormat::Capabilities);

#endif//FLOW_INTERFACE_FILE_FORMAT_H
