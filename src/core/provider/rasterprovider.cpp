//
// Created by km on 6/10/21.
//

#include <absl/strings/str_cat.h>

#include "rasterprovider.h"
#include <src/core/layer/layertree.h>
void gisl::RasterProvider::loadData(std::string_view theFileName) {
  gisl::DataProvider::loadData(theFileName);

  std::shared_ptr<LayerTree> layerTree = gisl::LayerTree::getSharedLayerTree();

  this->xSize = this->poDS->GetRasterXSize();
  this->ySize = this->poDS->GetRasterYSize();

  this->layerCount = this->poDS->GetRasterCount();
  for (int i = 0; i < this->layerCount; ++i) {
    auto name = absl::StrCat(theFileName, ": ");

    //    layerTree->append(name, this->poDS->GetRasterBand(i));
  }
}
