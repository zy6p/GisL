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

        explicit DataProvider( std::string_view theFileName, const std::string &theFileEncoding = "utf-8" ) {
            log = Log::getLog();
            this->fid = ++DataProvider::fidSeed;
            this->loadData(theFileName, theFileEncoding);
        }

        virtual void loadData( std::string_view theFileName, const std::string &theFileEncoding = "utf-8" ) = 0;

        constexpr bool hasError( ) const noexcept {
            return this->mErr == DataProviderErr::NoErr;
        }

        virtual ~DataProvider( ) = default;

    private:

        DataProviderErr mErr = DataProviderErr::NoErr;
        Log *log;

        int layerCount = 0;

        static int fidSeed;
        int fid;

    };
    int gisl::DataProvider::fidSeed = 0;

}

#endif //GISL_DATAPROVIDER_H
