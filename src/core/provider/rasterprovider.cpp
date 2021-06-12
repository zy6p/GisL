//
// Created by km on 6/10/21.
//

#include <absl/strings/str_cat.h>

#include "rasterprovider.h"
#include <src/core/layer/layertree.h>
void gisl::RasterProvider::loadData(const std::string& theFileName) {
  gisl::DataProvider::loadData(theFileName);
  this->xSize = this->poDS->GetRasterXSize();
  this->ySize = this->poDS->GetRasterYSize();

  LayerTree* layerTree = gisl::LayerTree::getLayerTree();

  this->layerCount = this->poDS->GetRasterCount();
  pmBand.resize(this->layerCount);
  int i = 0;
  RasterBand::seed(this->fid);
  for (auto j : this->poDS->GetBands()) {
    std::string name =
        absl::StrCat(theFileName, ".", std::to_string(i), ".png");
    pmBand[i] = std::make_shared<RasterBand>(RasterBand());
    pmBand[i]->setGDALLayer(j);
    pmBand[i]->matrixToStr();
    pmBand[i]->setFileName(name);
    pmBand[i]->toImg();
    layerTree->append(pmBand[i]->getFid(), pmBand[i].get());
    i++;
  }
}
gisl::RasterProvider::RasterProvider() : DataProvider() {
  this->gdalOpenFlag = GDAL_OF_RASTER;
}
