/*!
 * @file layerpropertytable.h
 * @author omega
 * @date 24/12/2020
 *
 * @brief layer StdStringMap table
 * @details
 *
 *
 */

#ifndef GISL_LAYERPROPERTYTABLE_H
#define GISL_LAYERPROPERTYTABLE_H

#include <ogr_feature.h>
#include <string>

#include "featureproperty.h"

namespace gisl {
class LayerPropertyTable {
public:
  explicit LayerPropertyTable(int fidOfLayer);

  void getFeatureCount(int count);

  void append(int fidOfFeature, FeatureProperty& poFeatureProperty);

  ~LayerPropertyTable();

private:
  int fid;
  int featureCount;
  FeatureProperty** pmFeatureProperty;
};
} // namespace gisl

#endif // GISL_LAYERPROPERTYTABLE_H
