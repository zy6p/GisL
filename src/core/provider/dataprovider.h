//
// Created by omega on 14/12/2020.
//

#ifndef GISL_DATAPROVIDER_H
#define GISL_DATAPROVIDER_H

#include <string>

#include "src/utils/log.h"

namespace gisl {

    /*!
     * @brief basic unit of geometry features
     */
    class DataProvider {
    public:

        enum class DataProviderErr {
            NoErr = 0,
            ErrDataSource,
            ErrCoding,
            ErrFileName
        };

        constexpr int getLayerCount( ) const noexcept {
            return this->layerCount;
        }

        DataProvider() {
            log = Log::getLog();
            this->fid = DataProvider::fidSeed++;
        }

        virtual void loadData( std::string_view theFileName, const std::string &theFileEncoding = "utf-8" ) = 0;

        virtual ~DataProvider( ) = default;

        constexpr bool hasError( ) const noexcept {
            return this->mErr == DataProviderErr::NoErr;
        }

    protected:
        Log *log;

        int layerCount = 0;

        static int fidSeed;
        int fid;

        DataProviderErr mErr = DataProviderErr::NoErr;
    };

}

#endif //GISL_DATAPROVIDER_H
