#ifndef FLOW_SCRIPT_MODULE_H
#define FLOW_SCRIPT_MODULE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class ScriptModule : public QObject
{
  Q_OBJECT

public:
  explicit ScriptModule(QObject *parent = nullptr);
  ~ScriptModule() override;
};

#endif//FLOW_SCRIPT_MODULE_H
