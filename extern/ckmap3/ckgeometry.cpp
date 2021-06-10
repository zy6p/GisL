#include "ckgeometry.h"
#include <iostream>

using namespace std;

CKGeometry::CKGeometry() {
  geo_type = -1;
  envelop[0] = 999999999.0;
  envelop[1] = 999999999.0;
  envelop[2] = -999999999.0;
  envelop[3] = -999999999.0;
}

CKGeometry::CKGeometry(int type) { this->geo_type = type; }

CKGeometry::~CKGeometry() { cout << "dododoooooo" << endl; }
