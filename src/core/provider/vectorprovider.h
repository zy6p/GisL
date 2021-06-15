//
// Created by omega on 14/12/2020.
//

#ifndef GISL_VECTORPROVIDER_H
#define GISL_VECTORPROVIDER_H

#include <string>

#include <gdal_priv.h>
#include <ogrsf_frmts.h>

#include "core/provider/dataprovider.h"
#include "core/vector/vectorlayer.h"

namespace gisl {

/*!
 * @brief basic unit of geometry features
 */
class VectorProvider final : public DataProvider {
public:
    VectorProvider();
    void loadData(const std::string& theFileName) override;

    ~VectorProvider();
    void combinePrint(int band1, int band2, int band3) override;
    void
    combinePrint(int band1, int band2, int band3, PainterFactory& p) override;

private:
    GDALDataset* poDS;

    VectorLayer** pmVectorLayer;
};

} // namespace gisl

#endif // GISL_VECTORPROVIDER_H
