//
// Created by km on 6/10/21.
//

#include "rasterprovider.h"
void gisl::RasterProvider::loadData(std::string_view theFileName,
                                    const std::string &theFileEncoding) {
  poDS = ( GDALDataset * ) GDALOpenEx( theFileName.data(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr );
  if ( nullptr == poDS ) {
    mErr = DataProviderErr::ErrDataSource;
    log->append( QObject::tr( "<ERROR>: Could not open the geojson file" ));
    return;
  }
}
