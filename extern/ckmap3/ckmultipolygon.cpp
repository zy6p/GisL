#include "ckmultipolygon.h"
#include <GL/glu.h>
#include <QDebug>
#include <QOpenGLFunctions_3_2_Core>

CKMultiPolygon::CKMultiPolygon() {
  polygons = 0x00;
  plg_size = 0;
  envelop[0] = 999999999;
  envelop[1] = 999999999;
  envelop[2] = -999999999;
  envelop[3] = -999999999;
}

CKMultiPolygon::CKMultiPolygon(const QJsonArray &mplg) {
  plg_size = mplg.size();
  polygons = new CKPolygon *[mplg.size()];

  for (int i = 0; i < mplg.size(); i++) {
    polygons[i] = new CKPolygon(mplg[i].toArray());
  }
}

CKMultiPolygon::~CKMultiPolygon() {
  if (polygons != 0x00) {
    for (int i = 0; i < plg_size; i++) {
      if (polygons[i] != 0x00) {
        delete polygons[i];
        polygons[i] = 0x00;
      }
    }
    delete[] polygons;
    polygons = 0x00;
  }
}

double *CKMultiPolygon::getEnvelop() {
  double *te = 0x00;
  for (int i = 0; i < this->plg_size; i++) {
    te = polygons[i]->getEnvelop();
    envelop[0] = envelop[0] < te[0] ? envelop[0] : te[0];
    envelop[1] = envelop[1] < te[1] ? envelop[1] : te[1];
    envelop[2] = envelop[2] > te[2] ? envelop[2] : te[2];
    envelop[3] = envelop[3] > te[3] ? envelop[3] : te[3];
  }
  return envelop;
}

void CKMultiPolygon::draw(CKSymbolizer *pSymb) {
  for (int i = 0; i < this->plg_size; i++) {
    polygons[i]->draw(pSymb);
  }
}
