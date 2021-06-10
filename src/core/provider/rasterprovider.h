//
// Created by km on 6/10/21.
//

#ifndef GISL_RASTERPROVIDER_H
#define GISL_RASTERPROVIDER_H

#include <string>
#include <src/utils/log.h>
#include <gdal_priv.h>

namespace gisl {

    /*!
     * @brief RasterProvider
     */
    class RasterProvider {
    public:

        enum class RasterErr {
            NoErr = 0,
            ErrDataSource,
            ErrCoding,
            ErrFileName
        };

        constexpr int getLayerCount( ) const;

        RasterProvider( ) = default;

        explicit RasterProvider( const std::string &vectorFileName, const std::string &theFileEncoding = "utf-8" );

        void loadRaster( const std::string &theVectorFileName, const std::string &theFileEncoding = "utf-8" );

        bool hasError( );

        ~RasterProvider( );

    private:

        RasterErr mErr = RasterErr::NoErr;
        Log *log;

        GDALDataset *poDS;
        int layerCount;

        static int fidInRaster;
        int fid;

        void loadDataSource( const std::string &theVectorName, const std::string &theFileEncoding );
    };

}

#endif //GISL_RASTERPROVIDER_H
