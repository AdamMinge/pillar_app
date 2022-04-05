#ifndef FLOW_ACTION_H
#define FLOW_ACTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/action/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  ACTION_API QAction *createActionWithShortcut(
    const QIcon &icon, QString &text,
    const QKeySequence &key_sequence = QKeySequence{},
    QObject *parent = nullptr);
  ACTION_API QAction *createActionWithShortcut(
    const QString &text, const QKeySequence &key_sequence = QKeySequence{},
    QObject *parent = nullptr);
  ACTION_API QAction *createActionWithShortcut(
    const QKeySequence &key_sequence = QKeySequence{},
    QObject *parent = nullptr);

}// namespace utils

#endif//FLOW_ACTION_H
