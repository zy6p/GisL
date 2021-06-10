//
// Created by km on 6/10/21.
//

#include "rasterprovider.h"
#include <src/core/layertree.h>
void gisl::RasterProvider::loadData(std::string_view theFileName,
                                    const std::string &theFileEncoding) {
  if (theFileName.empty()) {
    this->mErr = DataProviderErr::ErrDataSource;
    log->append(QObject::tr("<ERROR>: Empty filename given"));
    return;
  }

  CPLSetConfigOption("SHAPE_ENCODING", "");
  poDS = (GDALDataset *)GDALOpenEx(theFileName.data(), GDAL_OF_RASTER, nullptr,
                                   nullptr, nullptr);
  if (nullptr == poDS) {
    mErr = DataProviderErr::ErrDataSource;
    log->append(QObject::tr("<ERROR>: Could not open the file"));
    return;
  }
  LayerTree *layerTree = LayerTree::getLayerTree();

  layerCount = poDS->GetLayerCount();
}
