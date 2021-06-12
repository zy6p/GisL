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
