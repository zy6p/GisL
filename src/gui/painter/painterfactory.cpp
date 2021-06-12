/*!
 * @author tau
 * @date 1/1/21
 */

#include "painterfactory.h"
#include "src/core/layer/layertree.h"

void gisl::PainterFactory::getEnvelope(gisl::Rectangle& rectangle) {
  if (nullptr == pmEnvelope) {
    pmEnvelope = &rectangle;
  } else {
    pmEnvelope->merge(rectangle);
  }
}

gisl::Sld* gisl::PainterFactory::getSld() const { return pmSld; }

void gisl::PainterFactory::setSld(gisl::Sld* pSld) {
  PainterFactory::pmSld = pSld;
}

void gisl::PainterFactory::setRandSld() { pmSld->rand(layerFid); }

void gisl::PainterFactory::getLayerFid(int fid) { layerFid = fid; }
