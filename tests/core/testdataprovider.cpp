//
// Created by km on 6/10/21.
//

#define CATCH_CONFIG_MAIN

#include <memory>
#include <string>

#include <catch2/catch.hpp>

#include "core/provider/rasterprovider.h"
#include "core/provider/vectorprovider.h"
#include "gisl_config.h"

/*
TEST_CASE("VectorProvider::loadData") {
  auto pVectorProvider =
      std::make_unique<gisl::VectorProvider>(gisl::VectorProvider());
  std::string fileName = STRINGIFY(TEST_DATA_DIR) "qu.geojson";
  pVectorProvider->loadData(fileName);

  CHECK(pVectorProvider->getLayerCount() == 1);
}
*/

TEST_CASE("RasterProvider::loadData") {
  auto pRasterProvider =
      std::make_unique<gisl::RasterProvider>(gisl::RasterProvider());
  std::string fileName = STRINGIFY(TEST_DATA_DIR) "fwi-200902.tif";
  qDebug("%s", fileName.c_str());
  pRasterProvider->loadData(fileName);

  CHECK(pRasterProvider->getLayerCount() == 1);
}
