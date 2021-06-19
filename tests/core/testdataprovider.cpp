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

struct TestCase {
    std::string fileName;
    int layerCount;
};

/*
TEST_CASE("VectorProvider") {
  auto pVectorProvider =
      std::make_unique<gisl::VectorProvider>(gisl::VectorProvider());
  std::string fileName = STRINGIFY(TEST_DATA_DIR) "qu.geojson";
  pVectorProvider->loadData(fileName);

  CHECK(pVectorProvider->getLayerCount() == 1);
}
*/

TEST_CASE("RasterProvider") {
    auto testCase = GENERATE(
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif", 4},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/2/wuce.tif", 3},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/2/wuce_point.tif", 3},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/2/wucesource.tif", 3},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "fwi-200902.tif", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B1.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B2.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B3.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B4.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B5.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B7.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B1.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B2.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B3.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B4.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B5.TIF", 1},
                        TestCase{STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B7.TIF", 1});
    auto pRasterProvider =
        std::make_unique<gisl::RasterProvider>(gisl::RasterProvider());
    pRasterProvider->loadData(testCase.fileName);

    CHECK(pRasterProvider->getLayerCount() == testCase.layerCount);
}
