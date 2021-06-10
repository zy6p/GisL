/*!
 * @author tau
 * @date 12/20/20
 */

#ifndef GISL_VECTORLAYER_H
#define GISL_VECTORLAYER_H

#include <ogrsf_frmts.h>
#include <string>
#include <vector>

#include "src/core/spatialreference.h"
#include "src/core/vector/layerpropertytable.h"
#include "src/utils/log.h"
#include "vectorfeature.h"

namespace gisl {
class VectorLayer {
public:
  static void seed(int fidInVector);

  explicit VectorLayer(OGRLayer &poLayer);

  VectorLayer &operator=(const VectorLayer &rhs);

  int getFeatureCount() const;

  void draw(PainterFactory &p);

  Rectangle *getEnvelope() const;

  OGRLayer *getOgrLayer() const;

  VectorFeature **getFeature() const;

  ~VectorLayer();

private:
  static int fidInLayer;
  int fid;

  SpatialReference *pmCrs;

  int featureCount;

  Log *log;

  OGRLayer *pmLayer;
  OGREnvelope *pmExtent;

  void initEnvelope();

  VectorFeature **pmFeature;

  LayerPropertyTable *pmLayerPropertyTable;
};
} // namespace gisl

#endif // GISL_VECTORLAYER_H
