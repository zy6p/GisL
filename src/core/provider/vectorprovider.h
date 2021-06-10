//
// Created by omega on 14/12/2020.
//

#ifndef GISL_VECTORPROVIDER_H
#define GISL_VECTORPROVIDER_H

#include <string>

#include <ogrsf_frmts.h>
#include <gdal_priv.h>

#include "src/core/provider/dataprovider.h"
#include "src/core/vectorlayer.h"

namespace gisl {

    /*!
     * @brief basic unit of geometry features
     */
    class VectorProvider final : public DataProvider {
    public:
        void loadData( std::string_view theFileName, const std::string &theFileEncoding = "utf-8" ) override;

        ~VectorProvider( );

    private:
        GDALDataset *poDS;

        VectorLayer **pmVectorLayer;

        void loadDataSource( const std::string &theVectorName, const std::string &theFileEncoding );
    };

}

#endif //GISL_VECTORPROVIDER_H
