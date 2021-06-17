//
// Created by km on 6/10/21.
//

#ifndef GISL_RASTERPROVIDER_H
#define GISL_RASTERPROVIDER_H

#include <gdal_priv.h>
#include <string>

#include "core/raster/rasterband.h"
#include "dataprovider.h"
#include "utils/log.h"
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
    [[nodiscard]] const std::vector<std::shared_ptr<RasterBand>>&
            getPmBand() const;
    void setContrastEnhancementMethod(RasterBand::ContrastEnhancementMethod m);

    [[nodiscard]] int getXSize() const;
    [[nodiscard]] int getYSize() const;

private:
    std::vector<std::shared_ptr<RasterBand>> pmBand;
    RasterBand::ContrastEnhancementMethod contrastEnhancementMethod =
        RasterBand::ContrastEnhancementMethod::StretchToCumulative96RealMinMax;
    int xSize = 0;
    int ySize = 0;
};

} // namespace gisl

#endif // GISL_RASTERPROVIDER_H
