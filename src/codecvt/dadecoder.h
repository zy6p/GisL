//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DADECODER_H
#define GISL_DADECODER_H

#include "dacodecvt.h"
#include "daunit.h"
#include <string>
#include <vector>

namespace gisl {

/*!
 * @brief decode binary file
 * @details operate binary file, decode and write text file
 */
class DaDecoder : public DaCodecvt {
public:
    enum DaCodecvt::CodecvtMode FileCoderType = DECODE;

    DaDecoder();

    /*!
     * @brief Construct function for DaDecoder
     * @param [in] binaryFilename
     * @bug string can not be in construct
     */
    explicit DaDecoder(std::string binaryFilename);

    ~DaDecoder();

    void writeTextFile(std::string textFilename);

    void loadBinaryFile(std::string binaryFilename);

    /*!
     * @brief decode binary
     */
    void decode();

private:
    int loadBinaryFile2Text();

    /*!
     * @warning do not delete last *ptr in a **ptr
     * @param ifs
     */
    void loadUnitInFile(std::ifstream& ifs);

    int findFilesize(std::ifstream& ifs);

    void units2text();

    int initSize(std::ifstream& ifs);

    /*!
     *
     * @warning std::sort params are stl containers not *ptr
     */
    void sortUnits();

    void vectorSort();

    void quickSort(int left, int right);
};

} // namespace gisl
#endif // GISL_DADECODER_H