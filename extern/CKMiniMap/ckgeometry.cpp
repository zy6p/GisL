#include "ckgeometry.h"
#include <iostream>

using namespace std;

CKGeometry::CKGeometry( ) {
    geo_type = -1;
}

CKGeometry::CKGeometry( int type ) {
    this->geo_type = type;
}

CKGeometry::~CKGeometry( ) {
    cout << "dododoooooo" << endl;
}
