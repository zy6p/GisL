//
// Created by km on 6/10/21.
//

#ifndef GISL_RASTERPROVIDER_H
#define GISL_RASTERPROVIDER_H

#include <gdal_priv.h>
#include <src/utils/log.h>
#include <string>

#include "../raster/rasterband.h"
#include "dataprovider.h"
namespace gisl {

/*!
 * @brief RasterProvider
 */
class RasterProvider final : public DataProvider {
public:
  RasterProvider();
  void loadData(const std::string& theFileName) override;
  void combinePrint(int band1, int band2, int band3) override;
  void
  combinePrint(int band1, int band2, int band3, PainterFactory& p) override;
  int xSize = 0;
  int ySize = 0;

protected:
  std::vector<std::shared_ptr<RasterBand>> pmBand;
};

} // namespace gisl

#endif // GISL_RASTERPROVIDER_H
