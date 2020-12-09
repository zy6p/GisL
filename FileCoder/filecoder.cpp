//
// Created by beiyu on 2020-12-09.
//

#include <fstream>
#include "daencoder.h"
#include "filecoder.h"

namespace FileCoder {

    FileCoder::FileCoder() {
        this->clean();
    }

    void FileCoder::clean() {
        this->buffer = nullptr;
        this->binaryFilename.clear();
        this->textFilename.clear();
        this->textDisOrder.clear();
        this->textInOrder.clear();
        this->units.clear();
    }

    FileCoder::~FileCoder() {
        this->clean();
    }

    int FileCoder::fileSize(std::ifstream &ifs) {
        ifs.seekg(0, std::ifstream::end);
        int filesize = static_cast<int>(ifs.tellg());
        ifs.seekg(0, std::ifstream::beg);
        return filesize;
    }

}