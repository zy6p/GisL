#include "ckpoint.h"
#include <iostream>

using namespace std;

CKPoint::CKPoint( ) : CKGeometry( 0 ) {
    this->x = -1;
    this->y = -1;
    this->m = 0;
}

CKPoint::CKPoint( double x, double y ) : CKGeometry( 0 ) {
    this->x = x;
    this->y = y;
    this->m = 0;

//    cout<<x<<","<<y<<endl;
}

CKPoint::~CKPoint( ) {
    this->x = -1;
    this->y = -1;
    this->m = 0;
}

double *CKPoint::getEnvelop( ) {
    envelop[0] = x;
    envelop[1] = y;
    envelop[2] = x;
    envelop[3] = y;
    return envelop;
}

void CKPoint::draw( CKSymbolizer *pSymb ) {

}

double CKPoint::GetX( ) {
    return this->x;
}

double CKPoint::GetY( ) {
    return this->y;
}

