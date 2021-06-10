//
// Created by km on 6/10/21.
//

#ifndef GISL_RASTERPROVIDER_H
#define GISL_RASTERPROVIDER_H

#include <gdal_priv.h>
#include <src/utils/log.h>
#include <string>

#include "dataprovider.h"
namespace gisl {

/*!
 * @brief RasterProvider
 */
class RasterProvider final : public DataProvider {
public:
  void loadData(std::string_view theFileName) override;

protected:
  int xSize;
  int ySize;
};

} // namespace gisl

#endif // GISL_RASTERPROVIDER_H
