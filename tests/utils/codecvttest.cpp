//
// Created by beiyu on 2020-12-06.
//

#include "codecvt/dadecoder.h"
#include "codecvt/daencoder.h"

int main(int argc, char* argv[]) {
  GisL::DaEncoder encoder;
  encoder.loadTextFile2Text("data/practise_1/Decode2.txt");
  encoder.encode();
  encoder.writeBinaryFile("data/practise_1/Ddddecode2.da");
  //    encoder.clear();
  GisL::DaDecoder decoder;
  decoder.loadBinaryFile("data/practise_1/Ddddecode2.da");
  decoder.decode();
  decoder.writeTextFile("data/practise_1/BDsdDecode2.txt");
  return 1;
  //    GisL::DaEncoder *pEncoder = new GisL::DaEncoder();
  //    pEncoder->loadTextFile2Text("data/practise_1/Decode2.txt");
  //    pEncoder->encode();
  //    pEncoder->writeBinaryFile("data/practise_1/Ddddecode2.da");
  //    delete pEncoder;
  //    GisL::DaDecoder *pDecoder = new GisL::DaDecoder();
  //    pDecoder->loadBinaryFile("data/practise_1/Ddddecode2.da");
  //    pDecoder->decode();
  //    pDecoder->writeTextFile("data/practise_1/BDsdDecode2.txt");
  //    delete pDecoder;
  //    return 1;
}
