//
// Created by omega on 14/12/2020.
//

#include "geommultipoint.h"

#include "../../utils/ptroperate.h"

namespace gisl {

GeomMultiPoint::GeomMultiPoint(OGRMultiPoint& ogrMultiPoint)
    : AbstractGeometry(ogrMultiPoint) {
  mWkbType = AbstractGeometry::WkbType::MultiPoint;
  pmMultiPoint = &ogrMultiPoint;
}

GeomMultiPoint::~GeomMultiPoint() { GeomMultiPoint::clear(); }

Rectangle* GeomMultiPoint::boundary() const {
  Rectangle* p;
  pmMultiPoint->getEnvelope(p);
  return p;
}

void GeomMultiPoint::clear() { pmMultiPoint->empty(); }

bool GeomMultiPoint::isEmpty() const { return pmMultiPoint->IsEmpty(); }

OGRGeometry* GeomMultiPoint::getGeometry() const { return pmMultiPoint; }

void GeomMultiPoint::draw(PainterFactory& p) {
  for (auto point : pmMultiPoint) {
    p.drawPoint(*(new ExchangePointXY(point->getX(), point->getY())));
  }
}
} // namespace gisl
