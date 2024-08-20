/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/record/strategy.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractButton>
#include <QAbstractItemView>
#include <QAbstractSlider>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QEvent>
#include <QItemSelectionModel>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMouseEvent>
#include <QSpinBox>
#include <QTabBar>
#include <QTextEdit>
#include <QToolBox>
#include <QToolButton>
/* -------------------------------------------------------------------------- */
#include "aegis/server/plugin_manager.h"
namespace aegis {

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] int findTabIndex(QTabBar *tabbar, QAbstractButton *button) {
  if (tabbar->tabsClosable()) {
    for (auto i = 0; i < tabbar->count(); ++i) {
      const auto current_button = qobject_cast<QAbstractButton *>(
          tabbar->tabButton(i, QTabBar::RightSide));

      if (button == current_button) return i;
    }
  }

  return -1;
}

/* ------------------------------- RecordStrategy --------------------------- */

RecordStrategy::RecordStrategy(QObject *parent)
    : QObject(parent), m_widget(nullptr) {}

RecordStrategy::~RecordStrategy() = default;

void RecordStrategy::setWidget(QWidget *widget) {
  if (m_widget == widget) return;

  if (m_widget) {
    removeConnections(m_widget);
    m_widget->removeEventFilter(this);
  }

  m_widget = widget;

  if (m_widget) {
    installConnections(m_widget);
    m_widget->installEventFilter(this);
  }
}

QWidget *RecordStrategy::getWidget() const { return m_widget; }

void RecordStrategy::installConnections(QWidget *widget) { Q_UNUSED(widget); }

void RecordStrategy::removeConnections(QWidget *widget) {
  m_widget->disconnect(this);
}

/* ---------------------------- RecordButtonStrategy ------------------------ */

const int RecordButtonStrategy::type = qMetaTypeId<QAbstractButton>();

RecordButtonStrategy::RecordButtonStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordButtonStrategy::~RecordButtonStrategy() = default;

bool RecordButtonStrategy::eventFilter(QObject *obj, QEvent *event) {
  if (auto widget = getWidget(); widget == obj) {
    switch (event->type()) {
      case QEvent::MouseButtonRelease: {
        const auto button = qobject_cast<QAbstractButton *>(widget);
        Q_ASSERT(button);

        const auto mouse_event = static_cast<QMouseEvent *>(event);
        const auto mouse_position = mouse_event->position().toPoint();
        const auto button_rect = button->rect();
        if (!button_rect.contains(mouse_position)) break;

        onPressed();

        break;
      }

      case QEvent::KeyPress: {
        const auto key_event = static_cast<QKeyEvent *>(event);
        if (key_event->key() == Qt::Key_Space ||
            key_event->key() == Qt::Key_Return ||
            key_event->key() == Qt::Key_Enter) {
          onPressed();
        }

        break;
      }
    }
  }

  return QObject::eventFilter(obj, event);
}

void RecordButtonStrategy::onPressed() {
  const auto button = qobject_cast<QAbstractButton *>(getWidget());

  if (button->isCheckable()) {
    onToggled(!button->isChecked());
  } else {
    onClicked();
  }
}

void RecordButtonStrategy::onClicked() {
  qDebug() << "RecordButtonStrategy::onClicked";
}

void RecordButtonStrategy::onToggled(bool checked) {
  qDebug() << "RecordButtonStrategy::onToggled = " << checked;
}

/* --------------------------- RecordComboBoxStrategy ----------------------- */

const int RecordComboBoxStrategy::type = qMetaTypeId<QComboBox>();

RecordComboBoxStrategy::RecordComboBoxStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordComboBoxStrategy::~RecordComboBoxStrategy() = default;

void RecordComboBoxStrategy::installConnections(QWidget *widget) {
  auto combobox = qobject_cast<QComboBox *>(widget);
  Q_ASSERT(combobox);

  connect(combobox, &QComboBox::currentIndexChanged, this,
          &RecordComboBoxStrategy::onCurrentIndexChanged);
}

void RecordComboBoxStrategy::onCurrentIndexChanged(int index) {
  qDebug() << "RecordComboBoxStrategy::onCurrentIndexChanged = " << index;
}

/* --------------------------- RecordSpinBoxStrategy ------------------------ */

const int RecordSpinBoxStrategy::type = qMetaTypeId<QAbstractSpinBox>();

RecordSpinBoxStrategy::RecordSpinBoxStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordSpinBoxStrategy::~RecordSpinBoxStrategy() = default;

void RecordSpinBoxStrategy::installConnections(QWidget *widget) {
  if (auto spinbox = qobject_cast<QSpinBox *>(widget); spinbox) {
    connect(spinbox, &QSpinBox::valueChanged, this,
            QOverload<int>::of(&RecordSpinBoxStrategy::onValueChanged));
  } else if (auto spinbox = qobject_cast<QDoubleSpinBox *>(widget); spinbox) {
    connect(spinbox, &QDoubleSpinBox::valueChanged, this,
            QOverload<double>::of(&RecordSpinBoxStrategy::onValueChanged));
  } else {
    Q_ASSERT(false);
  }
}

void RecordSpinBoxStrategy::onValueChanged(double value) {
  qDebug() << "RecordSpinBoxStrategy::onValueChanged = " << value;
}

void RecordSpinBoxStrategy::onValueChanged(int value) {
  qDebug() << "RecordSpinBoxStrategy::onValueChanged = " << value;
}

/* ---------------------------- RecordSliderStrategy ------------------------ */

const int RecordSliderStrategy::type = qMetaTypeId<QAbstractSlider>();

RecordSliderStrategy::RecordSliderStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordSliderStrategy::~RecordSliderStrategy() = default;

void RecordSliderStrategy::installConnections(QWidget *widget) {
  auto slider = qobject_cast<QAbstractSlider *>(widget);
  Q_ASSERT(slider);

  connect(slider, &QAbstractSlider::valueChanged, this,
          &RecordSliderStrategy::onValueChanged);
}

void RecordSliderStrategy::onValueChanged(int value) {
  qDebug() << "RecordSliderStrategy::onValueChanged = " << value;
}

/* ---------------------------- RecordTabBarStrategy ------------------------ */

const int RecordTabBarStrategy::type = qMetaTypeId<QTabBar>();

RecordTabBarStrategy::RecordTabBarStrategy(QObject *parent)
    : RecordStrategy(parent), m_closing(false) {}

RecordTabBarStrategy::~RecordTabBarStrategy() = default;

void RecordTabBarStrategy::installConnections(QWidget *widget) {
  auto tabbar = qobject_cast<QTabBar *>(widget);
  Q_ASSERT(tabbar);

  connect(tabbar, &QTabBar::tabMoved, this, &RecordTabBarStrategy::onTabMoved);

  connect(tabbar, &QTabBar::currentChanged, this, [this](auto i) {
    if (!m_closing) onCurrentChanged(i);
    m_closing = false;
  });

  if (tabbar->tabsClosable()) {
    for (auto i = 0; i < tabbar->count(); ++i) {
      const auto button = qobject_cast<QAbstractButton *>(
          tabbar->tabButton(i, QTabBar::RightSide));

      connect(button, &QAbstractButton::released, this,
              [this, tabbar, button]() {
                m_closing = true;

                const auto i = findTabIndex(tabbar, button);
                Q_ASSERT(i >= 0);
                onTabClosed(i);
              });
    }
  }
}

void RecordTabBarStrategy::removeConnections(QWidget *widget) {
  RecordStrategy::removeConnections(widget);

  auto tabbar = qobject_cast<QTabBar *>(widget);
  Q_ASSERT(tabbar);

  if (tabbar->tabsClosable()) {
    for (auto i = 0; i < tabbar->count(); ++i) {
      const auto button = qobject_cast<QAbstractButton *>(
          tabbar->tabButton(i, QTabBar::RightSide));

      button->disconnect(this);
    }
  }
}

void RecordTabBarStrategy::onCurrentChanged(int index) {
  qDebug() << "RecordTabBarStrategy::onCurrentChanged = " << index;
}

void RecordTabBarStrategy::onTabClosed(int index) {
  qDebug() << "RecordTabBarStrategy::onTabClosed = " << index;
}

void RecordTabBarStrategy::onTabMoved(int from, int to) {
  qDebug() << "RecordTabBarStrategy::onTabMoved = (" << from << "," << to
           << ")";
}

/* ---------------------------- RecordToolBoxStrategy ----------------------- */

const int RecordToolBoxStrategy::type = qMetaTypeId<QToolBox>();

RecordToolBoxStrategy::RecordToolBoxStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordToolBoxStrategy::~RecordToolBoxStrategy() = default;

void RecordToolBoxStrategy::installConnections(QWidget *widget) {
  auto toolbox = qobject_cast<QToolBox *>(widget);
  Q_ASSERT(toolbox);

  connect(toolbox, &QToolBox::currentChanged, this,
          &RecordToolBoxStrategy::onCurrentChanged);
}

void RecordToolBoxStrategy::onCurrentChanged(int index) {
  qDebug() << "RecordToolBoxStrategy::onCurrentChanged = " << index;
}

/* ----------------------------- RecordMenuStrategy ------------------------- */

const int RecordMenuStrategy::type = qMetaTypeId<QMenu>();

RecordMenuStrategy::RecordMenuStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordMenuStrategy::~RecordMenuStrategy() = default;

bool RecordMenuStrategy::eventFilter(QObject *obj, QEvent *event) {
  if (auto widget = getWidget(); widget == obj) {
    switch (event->type()) {
      case QEvent::MouseButtonRelease: {
        const auto menu = qobject_cast<QMenu *>(widget);
        Q_ASSERT(menu);

        const auto mouse_event = static_cast<QMouseEvent *>(event);
        const auto mouse_position = mouse_event->position().toPoint();

        const auto action = menu->actionAt(mouse_position);
        if (!action) break;
        if (!action->isEnabled()) break;
        if (action != menu->activeAction()) break;

        const auto rect = menu->actionGeometry(action);
        if (!rect.contains(mouse_position)) break;

        onTriggered(action);

        break;
      }
    }
  }

  return QObject::eventFilter(obj, event);
}

void RecordMenuStrategy::onTriggered(QAction *action) {
  qDebug() << "RecordMenuStrategy::onTriggered = " << action->text();
}

/* --------------------------- RecordTextEditStrategy ----------------------- */

const int RecordTextEditStrategy::type = qMetaTypeId<QTextEdit>();

RecordTextEditStrategy::RecordTextEditStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordTextEditStrategy::~RecordTextEditStrategy() = default;

void RecordTextEditStrategy::installConnections(QWidget *widget) {
  auto textedit = qobject_cast<QTextEdit *>(widget);
  Q_ASSERT(textedit);

  connect(textedit, &QTextEdit::textChanged, this,
          &RecordTextEditStrategy::onTextChanged);
}

void RecordTextEditStrategy::onTextChanged() {
  qDebug() << "RecordTextEditStrategy::onTextChanged";
}

/* --------------------------- RecordLineEditStrategy ----------------------- */

const int RecordLineEditStrategy::type = qMetaTypeId<QLineEdit>();

RecordLineEditStrategy::RecordLineEditStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordLineEditStrategy::~RecordLineEditStrategy() = default;

void RecordLineEditStrategy::installConnections(QWidget *widget) {
  auto lineedit = qobject_cast<QLineEdit *>(widget);
  Q_ASSERT(lineedit);

  connect(lineedit, &QLineEdit::textChanged, this,
          &RecordLineEditStrategy::onTextChanged);
}

bool RecordLineEditStrategy::eventFilter(QObject *obj, QEvent *event) {
  if (auto widget = getWidget(); widget == obj) {
    switch (event->type()) {
      case QEvent::KeyPress: {
        const auto key_event = static_cast<QKeyEvent *>(event);
        const auto pressed_key = key_event->key();
        if (pressed_key != Qt::Key_Return && pressed_key != Qt::Key_Enter)
          break;

        onReturnPressed();

        break;
      }
    }
  }

  return QObject::eventFilter(obj, event);
}

void RecordLineEditStrategy::onTextChanged(const QString &text) {
  qDebug() << "RecordLineEditStrategy::onTextChanged = " << text;
}

void RecordLineEditStrategy::onReturnPressed() {
  qDebug() << "RecordLineEditStrategy::onReturnPressed";
}

/* --------------------------- RecordItemViewStrategy ----------------------- */

const int RecordItemViewStrategy::type = qMetaTypeId<QAbstractItemView>();

RecordItemViewStrategy::RecordItemViewStrategy(QObject *parent)
    : RecordStrategy(parent) {}

RecordItemViewStrategy::~RecordItemViewStrategy() = default;

void RecordItemViewStrategy::installConnections(QWidget *widget) {
  auto itemview = qobject_cast<QAbstractItemView *>(widget);
  Q_ASSERT(itemview);

  auto model = itemview->model();
  if (model) {
    connect(model, &QAbstractItemModel::dataChanged, this,
            &RecordItemViewStrategy::onDataChanged);
  }
}

void RecordItemViewStrategy::removeConnections(QWidget *widget) {
  auto itemview = qobject_cast<QAbstractItemView *>(widget);
  Q_ASSERT(itemview);

  auto model = itemview->model();
  if (model) {
    model->disconnect(this);
  }
}

void RecordItemViewStrategy::onDataChanged(const QModelIndex &topLeft,
                                           const QModelIndex &bottomRight,
                                           const QList<int> &roles) {
  qDebug() << "RecordItemViewStrategy::onDataChanged";
}

}  // namespace aegis
