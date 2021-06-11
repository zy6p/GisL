//
// Created by km on 6/10/21.
//

#ifndef GISL_RASTERPROVIDER_H
#define GISL_RASTERPROVIDER_H

#include <gdal_priv.h>
#include <src/utils/log.h>
#include <string>

#include "dataprovider.h"
#include "../raster/rasterband.h"
namespace gisl {

/*!
 * @brief RasterProvider
 */
class RasterProvider final : public DataProvider {
public:
  RasterProvider();
  void loadData(const std::string &theFileName) override;

protected:
  std::vector<std::shared_ptr<RasterBand>> pmBand;
};

} // namespace gisl

#endif // GISL_RASTERPROVIDER_H
