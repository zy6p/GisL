#include "ckdecoder.h"

#include <algorithm>
#include <fstream>
#include <iostream>

bool dcGreater(CKUnit &, CKUnit &);

CKDecoder::CKDecoder() {
  buffer = 0x00;
  units.clear();
  o_str.empty();
}

CKDecoder::~CKDecoder() {
  if (buffer != 0x00) {
    delete[] buffer;
    buffer = 0x00;
  }

  units.clear();
  o_str.empty();
}

using namespace std;

int CKDecoder::loadFile(std::string path) {
  string str;
  std::ifstream ifs; //(path,ios::binary);
  ifs.open(path, ios::binary);
  if (ifs.fail()) {
    cout << "文件未正常打开" << endl;
    return -1;
  }

  ifs.seekg(0, ifs.end);
  int file_size = ifs.tellg();
  int unit_size = file_size / (sizeof(int) + sizeof(char));
  ifs.seekg(0, ifs.beg);

  if (buffer != 0x00) {
    delete[] buffer;
    buffer = 0x00;
  }
  buffer = new char[file_size];
  ifs.read(buffer, file_size);

  CKUnit unit;
  int pos = 0;
  for (int i = 0; i < unit_size; i++) {
    unit.value = *(buffer + pos);
    pos += 1;
    unit.flag = *((int *)(buffer + pos));
    pos += 4;

    units.push_back(unit);
  }

  ifs.close();

  return 0;
}

string CKDecoder::decode() {
  if (units.size() < 1)
    return "未发现任何字符";
  sort(units.begin(), units.end(), dcGreater);

  for (int i = 0; i < units.size(); i++) {
    o_str += units[i].value;
  }

  return o_str;
}

int CKDecoder::outputResult(std::string oPath) {
  ofstream ofs(oPath);
  ofs.write(o_str.c_str(), o_str.size());
  return 0;
}

int CKDecoder::find_first_char(char ch) {
  int i = 0;
  while (1) {
    if (o_str[i] == ch) {
      cout << "第一个字符 " << ch << "的位置是" << i << endl;
      break;
    }

    //其他操作
    i++;
  }
  return 0;
}

int CKDecoder::find_all_chars(char ch) {
  int i = 0;
  int order = 0;
  while (1) {
    if (o_str[i] == ch) {
      cout << "第" << order << "个字符 " << ch << " 的位置是" << i << endl;
      order++;
      i++;
      continue;
    }
    //其他操作
    i++;
  }
  return 0;
}

bool dcGreater(CKUnit &u1, CKUnit &u2) { return u1.flag < u2.flag; }
