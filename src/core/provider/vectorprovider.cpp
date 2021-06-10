//
// Created by omega on 14/12/2020.
//

#include "vectorprovider.h"

#include <string>

#include "src/core/layer/layertree.h"
#include "src/core/vector/vectorlayer.h"
#include "src/utils/ptroperate.h"

namespace gisl {

void VectorProvider::loadData(std::string_view theFileName) {

  DataProvider::loadData(theFileName);

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