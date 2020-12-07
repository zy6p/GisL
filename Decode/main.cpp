//
// Created by beiyu on 2020-12-06.
//

#include "dadecoder.h"
#include <string>

int main(int argc, char *argv[]) {
    char filepath[] = "../practise_1/Encode3.da";
    DaDecoder decoder(filepath);
    decoder.writeIntoFile("../practise_1/Decode3.txt");
    return 1;
}
