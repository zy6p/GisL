#include "ckdecoder.h"
#include "ckencoder.h"
#include <iostream>

using namespace std;

int main() {
  char *src_path = "D:\\workstation\\teaching\\course\\oop "
                   "gis\\practice\\practise_1\\Encode3.txt";
  char *dest_path = "D:\\workstation\\teaching\\course\\oop "
                    "gis\\practice\\practise_1\\Encode3-1.da";

  CKEncoder encoder;
  encoder.loadTxtData(src_path);
  encoder.encode();
  encoder.outputFile(dest_path);

#if 1
  char *dest_b_path = "D:\\workstation\\teaching\\course\\oop "
                      "gis\\practice\\practise_1\\Encode3-1.txt";
  CKDecoder decoder;
  decoder.loadFile(dest_path);
  decoder.decode();
  decoder.outputResult(dest_b_path);
#endif
  return 0;
}
