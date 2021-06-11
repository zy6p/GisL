//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SPATIALREFERENCE_H
#define GISL_SPATIALREFERENCE_H

#include <ogr_spatialref.h>
#include <string>

namespace gisl {
/*!
 * @brief Coordinate Reference System
 */
class SpatialReference {
public:
  explicit SpatialReference(OGRSpatialReference& poSRS);

  void toWKT(std::string& outWkt);

  ~SpatialReference();

private:
  OGRSpatialReference* pmCRS;
};
} // namespace gisl

#endif // GISL_SPATIALREFERENCE_H
