//
// Created by omega on 14/12/2020.
//

#ifndef GISL_DATAPROVIDER_H
#define GISL_DATAPROVIDER_H

#include <QImage>
#include <gdal_priv.h>
#include <string>

#include "src/gui/painter/painterfactory.h"
#include "src/utils/log.h"

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

  virtual void combinePrint(int band1, int band2, int band3) = 0;
  virtual void
  combinePrint(int band1, int band2, int band3, PainterFactory& p) = 0;
  virtual void loadData(const std::string& theFileName);
  int getFid();

  virtual ~DataProvider();

  const std::string& getFileName() const;
  void setFileName(const std::string& fileName);

  bool hasError() const { return this->mErr != DataProviderErr::NoErr; }

protected:
  std::shared_ptr<Log> log;

  std::string fileName;

  uint gdalOpenFlag;
  GDALDataset* poDS = nullptr;
  int layerCount = 0;

  static int fidSeed;
  int fid;

  QImage qImage;

  DataProviderErr mErr = DataProviderErr::NoErr;
};

} // namespace gisl

#endif // GISL_DATAPROVIDER_H
