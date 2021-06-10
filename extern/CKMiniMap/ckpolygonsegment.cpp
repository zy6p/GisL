#include "ckpolygonsegment.h"

CKPolygonSegment::CKPolygonSegment() {
  pts = 0x00;
  pt_size = 0;
}

CKPolygonSegment::~CKPolygonSegment() {
  if (pts != 0x00) {
    for (int i = 0; i < pt_size; i++) {
      if (pts[i] != 0x00) {
        delete pts[i];
        pts[i] = 0x00;
      }
    }
    delete[] pts;
    pts = 0x00;
  }
}

CKPolygonSegment::CKPolygonSegment(const QJsonArray &seg) {
  pt_size = seg.size();
  pts = new CKPoint *[pt_size];
  QJsonArray pta;
  for (int i = 0; i < pt_size; i++) {
    pta = seg[i].toArray();
    pts[i] = new CKPoint(pta[0].toDouble(), pta[1].toDouble());
  }
}
