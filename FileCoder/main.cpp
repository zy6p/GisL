//
// Created by beiyu on 2020-12-06.
//

#include "dadecoder.h"
#include "daencoder.h"

int main(int argc, char *argv[]) {
    GisL::DaEncoder encoder;
    encoder.loadTextFile2Text("../FileCoder/practise_1/Decode2.txt");
    encoder.encode();
    encoder.writeBinaryFile("../FileCoder/practise_1/Ddddecode2.da");
    char filepath[] = "../FileCoder/practise_1/Ddddecode2.da";
    GisL::DaDecoder decoder;
    decoder.loadBinaryFile(filepath);
    decoder.decode();
    decoder.writeTextFile("../FileCoder/practise_1/Ddddecode2.txt");
    return 1;
}
