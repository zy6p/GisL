/*!
 * @file MError.h
 * @author omega 
 * @date 21/12/2020
 * 
 * @brief 程序的简要说明
 * @details 
 * @verbatim
 * 程序的详细说明。
 */

#ifndef GISL_MERROR_H
#define GISL_MERROR_H

namespace GisL {
    class MError {

    public:
        /*!
         * @brief vector MError
         */
        enum GisLError {
            NoError = 0,
            ErrInFileName,
            ErrDriverNotFound,
            ErrCreateDataSource,
            ErrCreateLayer,
            ErrAttributeTypeUnsupported,
            ErrAttributeCreationFailed,
            ErrSpatialRef,
            ErrExtent,
            ErrFeatureWriteFailed,
            ErrInvalidLayer,
            Canceled, //!< Opening was interrupted by manual cancellation
        };


    };
}

#endif //GISL_MERROR_H
