//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTIPOLYGON_H
#define GISL_GEOMMULTIPOLYGON_H

#include <ogr_geometry.h>

#include "abstractgeometry.h"

namespace gisl {

class GeomMultiPolygon : public AbstractGeometry {
public:
  explicit GeomMultiPolygon(OGRMultiPolygon& ogrMultiPolygon);

  Rectangle* boundary() const override;

  void clear() override;

  void draw(PainterFactory& p) override;

  bool isEmpty() const override;

  ~GeomMultiPolygon();

  OGRGeometry* getGeometry() const override;

private:
  OGRMultiPolygon* pmMultiPolygon;
};

} // namespace gisl

#endif // GISL_GEOMMULTIPOLYGON_H
