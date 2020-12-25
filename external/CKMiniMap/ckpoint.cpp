#include "ckpoint.h"
#include <iostream>

using namespace std;

CKPoint::CKPoint( ) {
    this->x = -1;
    this->y = -1;
    this->m = 0;
}

CKPoint::CKPoint( double x, double y ) {
    this->x = x;
    this->y = y;
    this->m = 0;

    cout << "x:" << x << " " << "y:" << y << endl;
}

CKPoint::~CKPoint( ) {
    this->x = -1;
    this->y = -1;
    this->m = 0;
}
