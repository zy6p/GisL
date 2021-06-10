#ifndef CKMULTIPOLYGON_H
#define CKMULTIPOLYGON_H

#include "ckgeometry.h"
#include "ckpolygon.h"
#include <QJsonArray>

class CKMultiPolygon : public CKGeometry {
public:
  CKMultiPolygon();

  CKMultiPolygon(const QJsonArray &mplg);

  ~CKMultiPolygon();

private:
  CKPolygon **polygons;
  int plg_size;

  // CKGeometry interface
public:
  double *getEnvelop() override;

  // CKGeometry interface
public:
  void draw(CKSymbolizer *pSymb) override;
};

#endif // CKMULTIPOLYGON_H
