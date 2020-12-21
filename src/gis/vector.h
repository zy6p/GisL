//
// Created by omega on 14/12/2020.
//

#ifndef GISL_VECTOR_H
#define GISL_VECTOR_H

#include <string>

#include <gdal/ogrsf_frmts.h>
#include <gdal/gdal_priv.h>

#include "vectorlayer.h"
#include "../utils/merror.h"

namespace GisL {

    /*!
     * @brief basic unit of geometry features
     */
    class Vector {
    public:

        static void seed();

        MError::VectorError hasError();

        std::string errorMessage();

        [[nodiscard]] int getLayerCount() const;

        Vector();

        VectorLayer **pmVectorLayer;

        explicit Vector(const std::string &vectorFileName, const std::string &theFileEncoding = "utf-8");

        void loadVector(const std::string &theVectorFileName, const std::string &theFileEncoding = "utf-8");

        ~Vector();


    private:
        MError::VectorError mError;
        std::string mErrorMessage;

        GDALDataset *poDS;
        int layerCount;

        static int fidInVector;
        int fid;

        void loadDataSource(const std::string &theVectorName, const std::string &theFileEncoding);

        static void registerOGRDriver();
    };

}

#endif //GISL_VECTOR_H
