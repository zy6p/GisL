#ifndef CKPOINT_H
#define CKPOINT_H

#include "ckgeometry.h"

class CKPoint : public CKGeometry {
public:
  CKPoint();

  CKPoint(double, double);

  ~CKPoint();

private:
  double x, y, m;
};

#endif // CKPOINT_H
