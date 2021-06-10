#ifndef CKLINE_H
#define CKLINE_H

#include "ckgeometry.h"

class CKLine : public CKGeometry {
public:
  CKLine();

  CKLine(double, double);

private:
  // CKGeometry interface
public:
  double *getEnvelop() override;
};

#endif // CKLINE_H
