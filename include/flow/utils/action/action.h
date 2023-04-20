#ifndef UTILS_ACTION_ACTION_H
#define UTILS_ACTION_ACTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/action/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

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

}  // namespace utils

#endif  // UTILS_ACTION_ACTION_H
