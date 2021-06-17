//
// Created by km on 6/17/21.
//
#include <catch2/catch.hpp>

#include "analysis/georeference.h"
#include "core/provider/rasterprovider.h"
#include "gisl_config.h"

TEST_CASE("GeoReference") {
  auto input = std::make_unique<gisl::RasterProvider>(gisl::RasterProvider());
  std::string fileName1 = STRINGIFY(TEST_DATA_DIR) "rs/2/wucesource.tif";
  input->loadData(fileName1);
  auto ref = std::make_unique<gisl::RasterProvider>(gisl::RasterProvider());
  std::string fileName2 = STRINGIFY(TEST_DATA_DIR) "rs/2/wuce.tif";
  input->loadData(fileName2);
  std::string fileName3 = STRINGIFY(TEST_DATA_DIR) "rs/2/transpos.csv";

  auto alg = new gisl::GeoReference();
  alg->realAlg(input.get(), ref.get(), fileName3);


  delete alg;
}
