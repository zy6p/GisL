#include "ckpoint.h"
#include <iostream>

using namespace std;

CKPoint::CKPoint() : CKGeometry(0) {
  this->x = -1;
  this->y = -1;
  this->m = 0;
}

CKPoint::CKPoint(double x, double y) : CKGeometry(0) {
  this->x = x;
  this->y = y;
  this->m = 0;

  //    cout<<x<<","<<y<<endl;
}

CKPoint::~CKPoint() {
  this->x = -1;
  this->y = -1;
  this->m = 0;
}
