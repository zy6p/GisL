//
// Created by omega on 6/10/21.
//

#include "dataprovider.h"
#include <src/core/layer/layertree.h>

int gisl::DataProvider::fidSeed = 0;

gisl::DataProvider::DataProvider() {
  log = Log::getSharedLog();
  this->fid = ++DataProvider::fidSeed;
  this->gdalOpenFlag = GDAL_OF_ALL;
  GDALAllRegister();
}

void gisl::DataProvider::loadData(const std::string& theFileName) {
  if (theFileName.empty()) {
    this->mErr = DataProviderErr::ErrDataSource;
    log->append(QObject::tr("<ERROR>: Empty filename given"));
    return;
  }

  CPLSetConfigOption("SHAPE_ENCODING", "");
  poDS = (GDALDataset*)GDALOpenEx(
      theFileName.c_str(),
      this->gdalOpenFlag,
      nullptr,
      nullptr,
      nullptr);
  if (nullptr == poDS) {
    mErr = DataProviderErr::ErrDataSource;
    log->append(QObject::tr("<ERROR>: Could not open the file"));
    return;
  }
}
gisl::DataProvider::~DataProvider() { GDALClose(this->poDS); }
