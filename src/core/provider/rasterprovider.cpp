//
// Created by km on 6/10/21.
//

#include "rasterprovider.h"

int fidInRaster = 0;

constexpr int gisl::RasterProvider::getLayerCount( ) const {
    return this->layerCount;
}

gisl::RasterProvider::RasterProvider( ) noexcept {
    GDALAllRegister();
    log = Log::getLog();
    fid = ++RasterProvider::fidInRaster;
}
gisl::RasterProvider::RasterProvider( const std::string &vectorFileName, const std::string &theFileEncoding ) {
    GDALAllRegister();
    log = Log::getLog();
    this->loadRaster( vectorFileName );
}

void gisl::RasterProvider::loadRaster( const std::string &theVectorFileName, const std::string &theFileEncoding ) {


}
