//
// Created by beiyu on 2020-12-06.
//

#include "dadecoder.h"
#include "daencoder.h"

int main(int argc, char *argv[]) {
//    char filepath[] = "../practise_1/Encode3.da";
//    FileCoder::DaDecoder decoder(filepath);
//    decoder.writeIntoFile("../practise_1/Decode3.txt");
    FileCoder::DaEncoder encoder;
    encoder.loadTextFile2Text("../FileCoder/practise_1/Decode2.txt");
    encoder.encode();
    return 1;
}
