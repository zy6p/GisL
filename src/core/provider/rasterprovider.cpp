//
// Created by km on 6/10/21.
//

#include <absl/strings/str_cat.h>

#include "rasterprovider.h"
#include <src/core/layer/layertree.h>
void gisl::RasterProvider::loadData(const std::string& theFileName) {
  gisl::DataProvider::loadData(theFileName);

  std::shared_ptr<LayerTree> layerTree = gisl::LayerTree::getSharedLayerTree();

  this->layerCount = this->poDS->GetRasterCount();
  pmBand.resize(this->layerCount);
  int i = 0;
  for (auto j : this->poDS->GetBands()) {
    pmBand[i] = std::make_shared<RasterBand>(RasterBand());
    pmBand[i]->setGDALLayer(j);
    pmBand[i]->matrixToStr();
    i++;
  }
  //    auto name = absl::StrCat(theFileName, ": ");
  //    layerTree->append(name, this->poDS->GetRasterBand(i));
}
gisl::RasterProvider::RasterProvider() : DataProvider() {
  this->gdalOpenFlag = GDAL_OF_RASTER;
}
