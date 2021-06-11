//
// Created by omega on 14/12/2020.
//

#include "vectorprovider.h"

#include <string>

#include "src/core/layer/layertree.h"
#include "src/core/vector/vectorlayer.h"
#include "src/utils/ptroperate.h"

namespace gisl {

void VectorProvider::loadData(const std::string &theFileName) {

  DataProvider::loadData(theFileName);

  LayerTree *layerTree = LayerTree::getLayerTree();

  VectorLayer::seed(fid);
  layerCount = poDS->GetLayerCount();
  pmVectorLayer = new VectorLayer *[layerCount];
  for (int i = 0; i < layerCount; ++i) {
    pmVectorLayer[i] = new VectorLayer();
    pmVectorLayer[i]->setOGRLayer(*poDS->GetLayer(i));
    layerTree->append(poDS->GetLayer(i)->GetName(), pmVectorLayer[i]);
  }
}

VectorProvider::~VectorProvider() {
  PtrOperate::clear(pmVectorLayer, layerCount);
}
VectorProvider::VectorProvider() : DataProvider() {
  this->gdalOpenFlag = GDAL_OF_VECTOR;
}

} // namespace gisl