/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_dock.h"

#include "flow_document/component/layers/layers_tree_model.h"
#include "flow_document/flow_document_action_handler.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/model/reverse_proxy_model.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_layers_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersDock::LayersDock(QWidget *parent)
    : QDockWidget(parent),
      m_ui(new Ui::LayersDock()),
      m_layers_model(new LayersTreeModel),
      m_filter_model(new utils::QtReverseProxyModel) {
  setObjectName(QLatin1String("Layers"));

  initUi();
  initConnections();

  retranslateUi();
}

LayersDock::~LayersDock() = default;

void LayersDock::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  m_document = document;

  if (m_document) {
    m_ui->m_layers_view->header()->setSectionResizeMode(
        LayersTreeModel::Column::NameColumn, QHeaderView::Stretch);
    m_ui->m_layers_view->header()->setSectionResizeMode(
        LayersTreeModel::Column::VisibleColumn, QHeaderView::Fixed);
    m_ui->m_layers_view->header()->setSectionResizeMode(
        LayersTreeModel::Column::LockedColumn, QHeaderView::Fixed);
  }

  m_layers_model->setDocument(m_document);
  m_ui->m_layers_view->setDocument(m_document);
}

FlowDocument *LayersDock::getDocument() const { return m_document; }

void LayersDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void LayersDock::searchLayers(const QString &search) {
  m_filter_model->setFilterWildcard(search);
}

void LayersDock::initUi() {
  m_ui->setupUi(this);

  m_filter_model->setSourceModel(m_layers_model.get());
  m_ui->m_layers_view->setModel(m_filter_model.get());

  m_filter_model->setFilterKeyColumn(LayersTreeModel::Column::NameColumn);
  m_filter_model->setRecursiveFilteringEnabled(true);

  const auto &handler = FlowDocumentActionHandler::getInstance();

  auto buttons_container = new QToolBar();
  buttons_container->setFloatable(false);
  buttons_container->setMovable(false);
  buttons_container->setIconSize(QSize(16, 16));

  auto new_layer_menu = handler.createNewLayerMenu(this);
  auto new_layer_button = new QToolButton();
  new_layer_button->setPopupMode(QToolButton::InstantPopup);
  new_layer_button->setMenu(new_layer_menu);
  new_layer_button->setIcon(new_layer_menu->icon());

  buttons_container->addWidget(new_layer_button);
  buttons_container->addAction(handler.getRemoveLayerAction());
  buttons_container->addAction(handler.getRaiseLayerAction());
  buttons_container->addAction(handler.getLowerLayerAction());
  buttons_container->addAction(handler.getDuplicateLayerAction());
  buttons_container->addSeparator();
  buttons_container->addAction(handler.getShowHideOtherLayersAction());
  buttons_container->addAction(handler.getLockUnlockOtherLayersAction());

  m_ui->m_toolbar_layout->addWidget(buttons_container);
}

void LayersDock::initConnections() {
  connect(m_ui->m_search_layers_edit, &QLineEdit::textChanged, this,
          &LayersDock::searchLayers);
}

void LayersDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document