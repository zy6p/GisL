//
// Created by omega on 14/12/2020.
//

#ifndef GISL_VECTORPROVIDER_H
#define GISL_VECTORPROVIDER_H

#include <string>

#include <ogrsf_frmts.h>
#include <gdal_priv.h>

#include "vectorlayer.h"
#include "../utils/log.h"
#include "../utils/gislobject.h"

namespace GisL {

    /*!
     * @brief basic unit of geometry features
     */
    class VectorProvider {
    public:

        enum VectorErr {
            NoErr = 0,
            ErrDataSource,
            ErrCoding,
            ErrFileName
        };

        int getLayerCount( ) const;

        VectorProvider( );

        explicit VectorProvider( const std::string &vectorFileName, const std::string &theFileEncoding = "utf-8" );

        void loadVector( const std::string &theVectorFileName, const std::string &theFileEncoding = "utf-8" );

        bool hasError( );

        ~VectorProvider( );

    private:

        VectorErr mErr = NoErr;
        Log *log;

        GDALDataset *poDS;
        int layerCount;

        static int fidInVector;
        int fid;

        VectorLayer **pmVectorLayer;

        void loadDataSource( const std::string &theVectorName, const std::string &theFileEncoding );

        static void registerOGRDriver( );
    };

}

#endif //GISL_VECTORPROVIDER_H
