#include "ckencoder.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

CKEncoder::CKEncoder() {
  buffer = 0x00;
  buf_size = 0;
  pUnits = 0x00;
}

CKEncoder::~CKEncoder() {
  if (buffer != 0x00) {
    delete[] buffer;
    buffer = 0x00;
  }

  if (pUnits != 0x00) {
    for (int i = 0; i < buf_size; i++) {
      if (pUnits[i] != 0x00) {
        delete pUnits[i];
        pUnits[i] = 0x00;
      }
    }
    delete[] pUnits;
    pUnits = 0x00;
  }

  if (randUnits != 0x00) {
    delete[] randUnits;
    randUnits = 0x00;
  }
  buf_size = 0;
}

int CKEncoder::loadTxtData(string path) {
  ifstream ifs;
  ifs.open(path);
  if (!ifs) {
    cout << "文件未正常打开" << endl;
    return -1;
  }

  //读取文本文件的逻辑
  ifs.seekg(0, ios_base::end);
  buf_size = ifs.tellg();
  ifs.seekg(0, ios_base::beg);

  if (buffer != 0x00) {
    delete[] buffer;
    buffer = 0x00;
  }

  buffer = new char[buf_size];
  ifs.read(buffer, buf_size);
  ifs.close();
}

void CKEncoder::encode() {
  srand(time(0x00));
  pUnits = new CKUnit *[buf_size];

  pUnits[0] = new CKUnit;
  pUnits[0]->value = buffer[0];
  pUnits[0]->flag = getRandNum(10000);

  CKUnit *tu = 0x00;
  for (int i = 1; i < buf_size; i++) {
    tu = new CKUnit(buffer[i], pUnits[i - 1]->flag + getRandNum(1000));
    pUnits[i] = tu;
    //        pUnits[i]=new CKUnit;
    //        pUnits[i]->value=buffer[i];
    //        pUnits[i]->flag=pUnits[i-1]->flag+getRandNum(1000);
  }

  //随机打乱顺序
  randUnits = new CKUnit *[buf_size];
  memset(randUnits, 0x00, buf_size * sizeof(CKUnit *));

  for (int i = 0; i < buf_size; i++) {
    randUnits[this->getValidPos(buf_size)] = pUnits[i];
  }
}

int CKEncoder::outputFile(string o_path) {
  ofstream ofs;
  ofs.open(o_path, ios::binary);
  if (!ofs) {
    return -1;
  }

  for (int i = 0; i < buf_size; i++) {
    ofs.write(&(randUnits[i]->value), sizeof(char));
    ofs.write((char *)(&(randUnits[i]->flag)), sizeof(int));
  }

  ofs.close();
}

int CKEncoder::getRandNum(int n) { return rand() % n; }

int CKEncoder::getValidPos(int size) {
  int pos = getRandNum(size);

  while (randUnits[pos] != 0x00) {
    pos = getRandNum(size);
    if (randUnits[pos] == 0x00) {
      //            cout<<pos<<endl;
      return pos;
    }
  }
  //    cout<<pos<<endl;
  return pos;
}
