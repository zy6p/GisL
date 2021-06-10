#ifndef CKPOLYGONSEGMENT_H
#define CKPOLYGONSEGMENT_H

#include <QJsonArray>
#include <ckpoint.h>

class CKPolygonSegment : public CKGeometry {
public:
  CKPolygonSegment();

  ~CKPolygonSegment();

  CKPolygonSegment(const QJsonArray &seg);

private:
  CKPoint **pts;
  int pt_size;
};

#endif // CKPOLYGONSEGMENT_H
