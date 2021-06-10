//
// Created by beiyu on 2020-12-09.
//

#include "daencoder.h"
#include "dacodecvt.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <random>
#include <string>
#include <vector>

namespace gisl {

DaEncoder::DaEncoder() : DaCodecvt() {}

int DaEncoder::loadTextFile2Text(std::string textFilename) {
  clear();
  this->textFilename = std::move(textFilename);
  std::ifstream ifs;
  ifs.open(this->textFilename);
  unitCount = fileSize(ifs);
  char *charTextInOrder = new char[unitCount];
  ifs.read(charTextInOrder, unitCount);
  textInOrder = charTextInOrder;
  ifs.close();
  delete[] charTextInOrder;
  return 0;
}

void DaEncoder::encode() {
  int *pEncryptionIndexInOrder = encryptionIndexInOrder();
  pUnits = new DaUnit *[unitCount];
  for (int i = 0; i < unitCount; ++i) {
    pUnits[i] = new DaUnit(textInOrder[i], pEncryptionIndexInOrder[i]);
  }
  disOrderUnits();
  delete[] pEncryptionIndexInOrder;
}

int *DaEncoder::encryptionIndexInOrder() {
  std::default_random_engine e((unsigned)time(nullptr));
  std::uniform_int_distribution<> u(0, unitCount * unitCount);
  int *pEncryptionIndex = new int[unitCount];
  for (int i = 0; i < unitCount; ++i)
    *(pEncryptionIndex + i) = u(e);
  std::sort(pEncryptionIndex, pEncryptionIndex + unitCount - 1);
  return pEncryptionIndex;
}

void DaEncoder::disOrderUnits() {
  std::default_random_engine e((unsigned)time(nullptr));
  std::uniform_int_distribution<> u(0, unitCount - 1);
  for (int i = 0; i < unitCount / 2; ++i) {
    std::swap(*pUnits[i], *pUnits[u(e)]);
  }
}

void DaEncoder::writeBinaryFile(std::string binaryFilename) {
  this->binaryFilename = std::move(binaryFilename);
  std::ofstream ofs;
  int charSize = sizeof(char);
  int intSize = sizeof(int);
  ofs.open(this->binaryFilename, std::ios::out | std::ios::binary);
  for (int i = 0; i < unitCount; ++i) {
    ofs.write((char *)&(pUnits[i]->value), charSize);
    ofs.write((char *)&(pUnits[i]->index), intSize);
  }
  ofs.close();
}

DaEncoder::~DaEncoder() = default;
;

} // namespace gisl