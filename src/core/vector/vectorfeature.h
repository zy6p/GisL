/*!
 * @author tau
 * @date 12/20/20
 */

#ifndef GISL_VECTORFEATURE_H
#define GISL_VECTORFEATURE_H

#include <ogr_feature.h>
#include <string>

#include "src/core/geometry/abstractgeometry.h"
#include "src/core/vector/featureproperty.h"
#include "src/utils/log.h"

namespace gisl {
class VectorFeature {
public:
  static void seed(int fidInLayer);

  explicit VectorFeature(OGRFeature &poFeature);

  VectorFeature &operator=(const VectorFeature &rhs);

  int getFid() const;

  std::string getFieldAsString(const std::string &s);

  Rectangle *boundary();

  FeatureProperty *getPmFeatureProperty() const;

  void draw(PainterFactory &p);

  ~VectorFeature();

private:
  FeatureProperty *pmFeatureProperty;

  OGRFeature *pmFeature;

  static int fidInFeature;
  int fid;

  AbstractGeometry *pmGeometry;
  AbstractGeometry::WkbType geoType;

  void defineGeo();
};
} // namespace gisl

#endif // GISL_VECTORFEATURE_H
