//
// Created by beiyu on 2020-12-06.
//

#include "dadecoder.h"
#include "daencoder.h"

int main(int argc, char *argv[]) {
    FileCoder::DaEncoder encoder;
    encoder.loadTextFile2Text("../FileCoder/practise_1/Decode2.txt");
    encoder.encode();
    encoder.writeBinaryFile("../FileCoder/practise_1/Ddddecode2.da");
    char filepath[] = "../FileCoder/practise_1/Ddddecode2.da";
    FileCoder::DaDecoder decoder(filepath);
    decoder.writeIntoFile("../FileCoder/practise_1/Ddddecode2.txt");
    return 1;
}
