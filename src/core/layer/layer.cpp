//
// Created by omega on 6/10/21.
//

#include "layer.h"

int gisl::Layer::fidSeed = 100;
void gisl::Layer::seed(int seed) { Layer::fidSeed = seed * 100; }
gisl::Layer::Layer() {
  log = Log::getSharedLog();
  fid = ++Layer::fidSeed;
}
gisl::Layer::~Layer() {}
int gisl::Layer::getFid() { return fid; }
const std::string& gisl::Layer::getFileName() const { return fileName; }
void gisl::Layer::setFileName(const std::string& fileName) {
  Layer::fileName = fileName;
}
