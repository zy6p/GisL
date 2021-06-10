#ifndef CKPOLYGON_H
#define CKPOLYGON_H

#include "ckpolygonsegment.h"
#include <qjsonarray.h>

class CKPolygon : public CKGeometry {
public:
  CKPolygon();

  CKPolygon(const QJsonArray &plg);

  ~CKPolygon();

private:
  CKPolygonSegment **pSegs;
  int seg_size;
};

#endif // CKPOLYGON_H
