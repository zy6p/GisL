//
// Created by omega on 6/10/21.
//

#include "dataprovider.h"
#include <src/core/layertree.h>

int gisl::DataProvider::fidSeed = 0;

gisl::DataProvider::DataProvider() {
  log = Log::getSharedLog();
  this->fid = ++DataProvider::fidSeed;
}

void gisl::DataProvider::loadData(std::string_view theFileName,
                                  const std::string &theFileEncoding) {
  if (theFileName.empty()) {
    this->mErr = DataProviderErr::ErrDataSource;
    log->append(QObject::tr("<ERROR>: Empty filename given"));
    return;
  }

  CPLSetConfigOption("SHAPE_ENCODING", "");
  poDS = (GDALDataset *)GDALOpenEx(theFileName.data(), GDAL_OF_VECTOR, nullptr,
                                   nullptr, nullptr);
  if (nullptr == poDS) {
    mErr = DataProviderErr::ErrDataSource;
    log->append(QObject::tr("<ERROR>: Could not open the file"));
    return;
  }
}
gisl::DataProvider::~DataProvider() { GDALClose(this->poDS); }
