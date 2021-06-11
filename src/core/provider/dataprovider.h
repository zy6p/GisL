//
// Created by omega on 14/12/2020.
//

#ifndef GISL_DATAPROVIDER_H
#define GISL_DATAPROVIDER_H

#include <gdal_priv.h>
#include <string>

#include "../../utils/log.h"

namespace gisl {

/*!
 * @brief basic unit of geometry features
 */
class DataProvider {
public:
  enum class DataProviderErr {
    NoErr = 0,
    ErrDataSource,
    ErrCoding,
    ErrFileName
  };

  DataProvider();

  constexpr int getLayerCount() const noexcept { return this->layerCount; }

  virtual void loadData(const std::string& theFileName);

  virtual ~DataProvider();

  bool hasError() const { return this->mErr == DataProviderErr::NoErr; }

protected:
  std::shared_ptr<Log> log;

  uint gdalOpenFlag;
  GDALDataset* poDS = nullptr;
  int layerCount = 0;

  static int fidSeed;
  int fid;

  DataProviderErr mErr = DataProviderErr::NoErr;
};

} // namespace gisl

#endif // GISL_DATAPROVIDER_H
