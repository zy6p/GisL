/*!
 * @file featureproperty.h
 * @author omega
 * @date 24/12/2020
 *
 * @brief property of feature
 * @details
 *
 *
 */

#ifndef GISL_FEATUREPROPERTY_H
#define GISL_FEATUREPROPERTY_H

#include <ogr_feature.h>
#include <string>

namespace gisl {
class FeatureProperty {
public:
  /*!
   * @brief feature property
   * @param poFeature
   */
  explicit FeatureProperty(OGRFeature &poFeature);

  ~FeatureProperty();

private:
  OGRFeature *pmFeature;

  int propertyCount;
  OGRFieldDefn **pmPropertyDefn;
  std::string **pmPropertyValue;
};
} // namespace gisl

#endif // GISL_FEATUREPROPERTY_H
