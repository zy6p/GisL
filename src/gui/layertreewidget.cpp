//
// Created by km on 6/13/21.
//

#include <QFileInfo>

#include "layertreewidget.h"
#include "src/gui/render/chooserasterrgbwidget.h"

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
        //        pLayer->draw();
      }
    }
    //    auto* uiRasterChooseRgb = new ChooseRasterRgbWidget(this);
    //    uiRasterChooseRgb->show();
    //    uiRasterChooseRgb->initRgb(rgbBand);
    //    int count = pProvider->getLayerCount() - 3;
    //    if (count >= 0) {
    //      pProvider->combinePrint(count + 2, count + 1, count);
    //    }
  }

  QTreeWidget::update();
}
