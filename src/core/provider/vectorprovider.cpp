//
// Created by omega on 14/12/2020.
//

#include "vectorprovider.h"

#include <QObject>
#include <ogrsf_frmts.h>
#include <string>

#include "src/core/layertree.h"
#include "src/core/vectorlayer.h"
#include "src/utils/ptroperate.h"

namespace gisl {

void VectorProvider::loadData(std::string_view theFileName,
                              const std::string &theFileEncoding) {

  DataProvider::loadData(theFileName, theFileEncoding);

  LayerTree *layerTree = LayerTree::getLayerTree();

  VectorLayer::seed(fid);
  layerCount = poDS->GetLayerCount();
  pmVectorLayer = new VectorLayer *[layerCount];
  for (int i = 0; i < layerCount; ++i) {
    pmVectorLayer[i] = new VectorLayer(*poDS->GetLayer(i));
    layerTree->append(poDS->GetLayer(i)->GetName(), pmVectorLayer[i]);
  }
}

VectorProvider::~VectorProvider() {
  PtrOperate::clear(pmVectorLayer, layerCount);
}

} // namespace gisl