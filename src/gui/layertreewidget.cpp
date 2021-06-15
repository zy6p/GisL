//
// Created by km on 6/13/21.
//

#include <QFileInfo>

#include "gui/render/chooserasterrgbwidget.h"
#include "layertreewidget.h"

gisl::LayerTreeWidget::LayerTreeWidget(QWidget* parent) : QTreeWidget(parent) {
  layerTree = gisl::LayerTree::getLayerTree();
}
void gisl::LayerTreeWidget::updateLayerTree() {
  QStringList headers;
  headers << tr("fid") << tr("name");
  this->setHeaderLabels(headers);
  this->clear();
  for (auto [fid, pProvider] : layerTree->providerMap) {
    QStringList itemPair;
    QFileInfo f{QString::fromStdString(pProvider->getFileName())};
    itemPair << QString::number(fid) << f.fileName();
    auto* providerRoot = new QTreeWidgetItem(this, itemPair);
    QStringList rgbBand;
    for (auto [fidOfLayer, pLayer] : layerTree->layerMap) {
      if (fid == fidOfLayer / 100) {
        rgbBand << QString::fromStdString(std::to_string(fidOfLayer));
        QStringList nodePair;
        QFileInfo fl{QString::fromStdString(pLayer->getFileName())};
        nodePair << QString::number(fidOfLayer)
                 << fl.fileName().remove(fl.fileName().size() - 4, 4);
        new QTreeWidgetItem(providerRoot, nodePair);
      }
    }
  }

  QTreeWidget::update();
}
void gisl::LayerTreeWidget::setSelectionModel(
    QItemSelectionModel* selectionModel) {
  QTreeWidget::setSelectionModel(selectionModel);
}
void gisl::LayerTreeWidget::dropEvent(QDropEvent* event) {
  QTreeWidget::dropEvent(event);
}
