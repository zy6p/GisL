/*!
 * @author tau
 * @date 12/20/20
 */

#ifndef GISL_VECTORLAYER_H
#define GISL_VECTORLAYER_H

#include <ogrsf_frmts.h>
#include <string>
#include <vector>

#include "core/layer/layer.h"
#include "core/spatialreference.h"
#include "core/vector/layerpropertytable.h"
#include "utils/log.h"
#include "vectorfeature.h"

namespace gisl {
class VectorLayer final : public Layer {
public:
  void setOGRLayer(OGRLayer* poLayer);

  VectorLayer& operator=(const VectorLayer& rhs);

  int getFeatureCount() const noexcept;

  void draw(PainterFactory& p) override;

  Rectangle* getEnvelope() const;

  OGRLayer* getOgrLayer() const;

  VectorFeature** getFeature() const;

  ~VectorLayer();
  void draw() override;

private:
  int featureCount;

  OGRLayer* pmLayer;
  OGREnvelope* pmExtent;

  void initEnvelope();

  VectorFeature** pmFeature;

  LayerPropertyTable* pmLayerPropertyTable;
};
} // namespace gisl

#endif // GISL_VECTORLAYER_H
