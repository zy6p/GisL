//
// Created by km on 6/13/21.
//

#include <QFileInfo>

#include "layertreewidget.h"
#include "src/gui/render/rasterimgview.h"

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
    for (auto [fidOfLayer, pLayer] : layerTree->layerMap) {
      if (fid == fidOfLayer / 100) {
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
void gisl::LayerTreeWidget::on_item_double_clicked(
    QTreeWidgetItem* item,
    int column) {
  bool flag{false};
  int fid = item->text(0).toInt(&flag);
  //  auto* p = new RasterImgView(this);
  if (flag) {
    if (fid > 100) {
      //      layerTree->layerMap[fid]->draw(*p);
    } else {
      layerTree->providerMap[fid]->combinePrint(1, 2, 3);
    }
  }
  QTreeWidget::itemDoubleClicked(item, column);
}
