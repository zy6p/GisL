/*!
 * @file layerpropertytable.cpp
 * @author omega
 * @date 24/12/2020
 *
 * @brief layer StdStringMap table
 * @details
 *
 *
 */

#include "layerpropertytable.h"

#include "utils/ptroperate.h"

namespace gisl {

/*!
 * @brief init
 * @param fidOfLayer
 */
LayerPropertyTable::LayerPropertyTable(int fidOfLayer) {
  fid = fidOfLayer;
  featureCount = 0;
  pmFeatureProperty = nullptr;
}

void LayerPropertyTable::getFeatureCount(int count) {
  this->featureCount = count;
  pmFeatureProperty = new FeatureProperty*[featureCount];
}

void LayerPropertyTable::append(
    int fidOfFeature,
    FeatureProperty& poFeatureProperty) {
  pmFeatureProperty[fidOfFeature - fid * 100 - 1] = &poFeatureProperty;
}

LayerPropertyTable::~LayerPropertyTable() {
  PtrOperate::clear(pmFeatureProperty, featureCount);
}

} // namespace gisl
