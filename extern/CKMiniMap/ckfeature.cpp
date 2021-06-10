#include "ckfeature.h"
#include "ckmultipolygon.h"

CKFeature::CKFeature() { pGeom = 0X00; }

CKFeature::CKFeature(const QJsonObject &feat) {
  QJsonValue prop = feat["properties"];
  QJsonValue geom = feat["geometry"];

  // properties solution

  // geometry solution
  if (geom["type"].toString().compare("MultiPolygon") == 0) {
    this->pGeom = new CKMultiPolygon(geom["coordinates"].toArray());
  }
}

CKFeature::~CKFeature() {
  if (pGeom != 0x00) {
    delete pGeom;
    pGeom = 0x00;
  }
}
