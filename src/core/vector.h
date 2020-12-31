//
// Created by omega on 14/12/2020.
//

#ifndef GISL_VECTOR_H
#define GISL_VECTOR_H

#include <string>

#include <gdal/ogrsf_frmts.h>
#include <gdal/gdal_priv.h>

#include "vectorlayer.h"
#include "../utils/log.h"
#include "../utils/gislobject.h"

namespace GisL {

    /*!
     * @brief basic unit of geometry features
     */
    class Vector {
    public:

        enum VectorErr {
            NoErr = 0,
            ErrDataSource,
            ErrCoding,
            ErrFileName
        };

        int getLayerCount( ) const;

        Vector( );

        explicit Vector( const std::string &vectorFileName, const std::string &theFileEncoding = "utf-8" );

        void loadVector( const std::string &theVectorFileName, const std::string &theFileEncoding = "utf-8" );

        bool hasError( );

        ~Vector( );

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

#endif //GISL_VECTOR_H
