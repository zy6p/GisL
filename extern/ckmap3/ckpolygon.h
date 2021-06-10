#ifndef CKPOLYGON_H
#define CKPOLYGON_H

#include "cklinearring.h"
#include <qjsonarray.h>

class CKPolygon : public CKGeometry {
public:
  CKPolygon();

  CKPolygon(const QJsonArray &plg);

  ~CKPolygon();

private:
  CKLinearRing **pSegs;
  int seg_size;

  // CKGeometry interface
public:
  double *getEnvelop() override;

  // CKGeometry interface
public:
  void draw(CKSymbolizer *pSymb) override;
};

#endif // CKPOLYGON_H
